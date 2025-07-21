#include "rclcpp/rclcpp.hpp"
#include "arm_control/msg/ik_result.hpp"
#include "arm_control/msg/trajectory_point.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "motionlib.h"
#include <Eigen/Dense>
#include <thread>
#include <map>

using namespace std;
using namespace rclcpp;
using namespace Eigen;

class TrajectoryNode : public Node {
public:
    TrajectoryNode() : Node("trajectory_node") {
        traj_pub_ = this->create_publisher<arm_control::msg::TrajectoryPoint>("trajectory_point", 10);
        ik_sub_ = this->create_subscription<arm_control::msg::IKResult>(
            "ik_result", 10, bind(&TrajectoryNode::ik_callback, this, std::placeholders::_1));
        joint_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states", 20, bind(&TrajectoryNode::joint_callback, this, std::placeholders::_1));
        
        // 从参数服务器获取轨迹规划参数
        this->declare_parameter("trajectory_time", 4.0);
        this->declare_parameter("dt", 0.1);
        this->declare_parameter("sync_mode", false);
        
        this->get_parameter("trajectory_time", trajectory_time);
        this->get_parameter("dt", dt);
        this->get_parameter("sync_mode", sync_mode);
        
        RCLCPP_INFO(this->get_logger(), "Trajectory node initialized");
        RCLCPP_INFO(this->get_logger(), "Parameters: time=%.1fs, dt=%.3fs, sync_mode=%s",
                  trajectory_time, dt, sync_mode ? "ON" : "OFF");
    }

private:

    void ik_callback(const arm_control::msg::IKResult::SharedPtr msg) {
        if (!msg->success) {
            RCLCPP_WARN(this->get_logger(), "Ignoring failed IK result for %s", msg->arm_name.c_str());
            return;
        }
        std::vector<TrajectoryPoint> trajectory;
        if(msg->arm_name!="dual_arm"){
            // 获取起始和目标关节角
            VectorXd q_start(6), q_end(6);
            bool is_left = (msg->arm_name == "left_arm");
            
            if (is_left) {
                q_start = left_current;
            } else if (msg->arm_name == "right_arm") {
                q_start = right_current;
            } else {
                RCLCPP_WARN(this->get_logger(), "Unknown arm: %s", msg->arm_name.c_str());
                return;
            }
            
            for (int i = 0; i < 6; i++) q_end[i] = msg->joint_angles[i];
            
            // 生成关节空间轨迹
            RCLCPP_INFO(this->get_logger(), "Generating trajectory for %s (%.1fs)", 
                    msg->arm_name.c_str(), trajectory_time);
            
            trajectory = jointSpaceTrajectory(q_start, q_end, trajectory_time, dt, joint_limits);
            
            RCLCPP_INFO(this->get_logger(), "Generated %zu trajectory points", trajectory.size());
        }else{
            if(msg->joint_angles.size()!=12)RCLCPP_INFO(this->get_logger(),"the dual arm angles size is not 12");
            TrajectoryPoint point;
            VectorXd temp(12);
            for (int i = 0; i < 12; i++) temp[i] = msg->joint_angles[i];//双臂是12关节
            point.positions=temp;
            trajectory.push_back(point);
        }
 
        // 存储轨迹（同步模式）或立即执行（非同步模式）
        execute_trajectory(trajectory, msg->arm_name);
        
    }

    void joint_callback(const sensor_msgs::msg::JointState::SharedPtr msg) {
        // 更新当前关节角度
        for (size_t i = 0; i < msg->name.size(); i++) {
            if (msg->name[i] == "left_joint1") {
                for (int j = 0; j < 6; j++) left_current[j] = msg->position[i+j];
            } else if (msg->name[i] == "right_joint1") {
                for (int j = 0; j < 6; j++) right_current[j] = msg->position[i+j];
            }
        }
    }

    void execute_trajectory(const vector<TrajectoryPoint>& trajectory, const string& arm_name) {
        //单双轨迹
        int num=(arm_name=="dual_arm")?12:6;
        // 按时间顺序发布轨迹点
        for (size_t i = 0; i < trajectory.size(); i++) {
            const auto& pt = trajectory[i];
            auto msg = arm_control::msg::TrajectoryPoint();
            
            msg.arm_name = arm_name;
            msg.positions.assign(pt.positions.data(), pt.positions.data()+num);//num用在这
            msg.time_from_start = pt.time;
            
            traj_pub_->publish(msg);
            
            // 等待适当的时间间隔
            this_thread::sleep_for(chrono::duration<double>(dt));
        }
        
        RCLCPP_INFO(this->get_logger(), "Trajectory execution completed for %s", arm_name.c_str());
    }

    void check_and_execute_synchronized() {
        // 检查是否同时有左右臂的轨迹待执行
        if (pending_trajectories.size() < 2) return;
        
        if (pending_trajectories.count("left_arm") && pending_trajectories.count("right_arm")) {
            RCLCPP_INFO(this->get_logger(), "Executing synchronized trajectories for both arms");
            
            const auto& left_traj = pending_trajectories["left_arm"];
            const auto& right_traj = pending_trajectories["right_arm"];
            
            // 计算最长轨迹的点数
            size_t max_points = max(left_traj.size(), right_traj.size());
            
            // 同步执行轨迹
            for (size_t i = 0; i < max_points; i++) {
                // 发布左臂轨迹点
                if (i < left_traj.size()) {
                    auto msg = arm_control::msg::TrajectoryPoint();
                    msg.arm_name = "left_arm";
                    msg.positions.assign(left_traj[i].positions.data(), left_traj[i].positions.data()+6);
                    msg.time_from_start = left_traj[i].time;
                    traj_pub_->publish(msg);
                }
                
                // 发布右臂轨迹点
                if (i < right_traj.size()) {
                    auto msg = arm_control::msg::TrajectoryPoint();
                    msg.arm_name = "right_arm";
                    msg.positions.assign(right_traj[i].positions.data(), right_traj[i].positions.data()+6);
                    msg.time_from_start = right_traj[i].time;
                    traj_pub_->publish(msg);
                }
                
                // 等待适当的时间间隔
                this_thread::sleep_for(chrono::duration<double>(dt));
            }
            
            // 清除已执行的轨迹
            pending_trajectories.clear();
            RCLCPP_INFO(this->get_logger(), "Synchronized trajectory execution completed");
        }
    }

    Publisher<arm_control::msg::TrajectoryPoint>::SharedPtr traj_pub_;
    Subscription<arm_control::msg::IKResult>::SharedPtr ik_sub_;
    Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub_;
    
    VectorXd left_current = VectorXd::Zero(6);
    VectorXd right_current = VectorXd::Zero(6);
    
    double trajectory_time = 5.0;  // 轨迹总时间（秒）
    double dt = 0.01;             // 时间步长（秒）
    bool sync_mode = false;       // 同步模式开关
    
    map<string, vector<TrajectoryPoint>> pending_trajectories;
    
    // 关节限制（与IK节点一致）
    vector<pair<double, double>> joint_limits = {
        {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI},
        {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI},
    };
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<TrajectoryNode>());
    rclcpp::shutdown();
    return 0;
}