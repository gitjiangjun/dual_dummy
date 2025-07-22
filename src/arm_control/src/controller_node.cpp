#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "arm_control/msg/trajectory_point.hpp"
#include "arm_control/msg/control_command.hpp"
#include <Eigen/Dense>
#include <vector>
#include <string>
#include "rclcpp_action/rclcpp_action.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"

using namespace std;
using namespace rclcpp;
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFJT = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;

class ArmControllerNode : public Node {
public:
    ArmControllerNode() : Node("arm_controller_node") {
        // 初始化关节名称（与URDF匹配）
        left_arm_joints = {"left_joint1", "left_joint2", "left_joint3", 
                          "left_joint4", "left_joint5", "left_joint6"};
        right_arm_joints = {"right_joint1", "right_joint2", "right_joint3", 
                           "right_joint4", "right_joint5", "right_joint6"};
        left_hand_joints = {"left_figer1","left_figer2"};
        right_hand_joints = {"right_figer1","right_figer2"};
        
        // 初始化关节位置
        current_left_arm = Eigen::VectorXd::Zero(6);
        current_right_arm = Eigen::VectorXd::Zero(6);
        current_left_hand = Eigen::Vector2d::Zero(2);  // 0=打开, 0.028=闭合
        current_right_hand = Eigen::Vector2d::Zero(2);
        
        // 订阅轨迹点和控制命令
        traj_sub_ = this->create_subscription<arm_control::msg::TrajectoryPoint>(
            "trajectory_point", 10, 
            bind(&ArmControllerNode::trajectory_callback, this, std::placeholders::_1));
        
        cmd_sub_ = this->create_subscription<arm_control::msg::ControlCommand>(
            "control_command", 10,
            bind(&ArmControllerNode::command_callback, this, std::placeholders::_1));
        //连接真实机械臂
        left_client_=rclcpp_action::create_client<FollowJointTrajectory>(this,"left_arm_controller/follow_joint_trajectory");
        right_client_=rclcpp_action::create_client<FollowJointTrajectory>(this,"right_arm_controller/follow_joint_trajectory");

        // 发布关节状态//机械臂模型控制，但是dummy2_arm_controller.py中有/joint_states反馈
        //joint_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 20);
        //timer_ = this->create_wall_timer(10ms, bind(&ArmControllerNode::publish_joint_states, this));
        
        RCLCPP_INFO(this->get_logger(), "Arm controller node initialized");
    }

private:
    void trajectory_callback(const arm_control::msg::TrajectoryPoint::SharedPtr msg) {
        if(msg->arm_name=="dual_arm"){
            for (int i = 0; i < 6; i++) current_left_arm[i] = msg->positions[i];
            for (int i = 6; i < 12; i++) current_right_arm[i-6] = msg->positions[i];
            RCLCPP_DEBUG(this->get_logger(), "Updated dual arm positions");
        }
        // 验证消息有效性
        if (msg->positions.size() != 6) {
            RCLCPP_ERROR(this->get_logger(), "Invalid trajectory point received: %zu positions (expected 6)", 
                       msg->positions.size());
            return;
        }
        
        // 关节限位检查
        bool valid = true;
        for (size_t i = 0; i < 6; i++) {
            if (msg->positions[i] < joint_limits[i].first || 
                msg->positions[i] > joint_limits[i].second) {
                RCLCPP_WARN(this->get_logger(), "Joint %zu out of limits: %.3f (allowed [%.3f, %.3f])", 
                          i, msg->positions[i], joint_limits[i].first, joint_limits[i].second);
                valid = false;
            }
        }
        
        // 应用安全限制
        if (valid) {
            if (msg->arm_name == "left_arm") {
                for (int i = 0; i < 6; i++) current_left_arm[i] = msg->positions[i];
                RCLCPP_DEBUG(this->get_logger(), "Updated left arm positions");
            } else if (msg->arm_name == "right_arm") {
                for (int i = 0; i < 6; i++) current_right_arm[i] = msg->positions[i];
                RCLCPP_DEBUG(this->get_logger(), "Updated right arm positions");
            }
        } else {
            RCLCPP_WARN(this->get_logger(), "Trajectory point discarded due to joint limits violation");
        }

        send_trajectory_to_dummy2();
    }

    void command_callback(const arm_control::msg::ControlCommand::SharedPtr msg) {
        // 处理夹爪命令
        if (msg->command_type == "gripper") {
            double target_pos = (msg->gripper_state == "close") ? 0.0 : 0.028;
            Eigen::Vector2d target_pos_1;
            target_pos_1<<target_pos,target_pos;
            if (msg->arm_name == "left_arm") {
                current_left_hand = target_pos_1;
            } else if (msg->arm_name == "right_arm") {
                current_right_hand = target_pos_1;
            } else if (msg->arm_name == "both_arms") {
                current_left_hand = target_pos_1;
                current_right_hand = target_pos_1;
            }
            
            RCLCPP_INFO(this->get_logger(), "Set %s gripper to %s", 
                      msg->arm_name.c_str(), msg->gripper_state.c_str());
        }
    }

    void send_trajectory_to_dummy2(){
        send_trajectory_to_left();
        send_trajectory_to_right();
    }
    void send_trajectory_to_left()
    {
        if (!left_client_->wait_for_action_server(1s)) {
            RCLCPP_ERROR(this->get_logger(), "Dummy2 left action server not available");
            return;
        }
        auto left_goal_msg=FollowJointTrajectory::Goal();
        left_goal_msg.trajectory.joint_names=left_arm_joints;
        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.positions=std::vector<double>(current_left_arm.data(),current_left_arm.data()+6);
        point.time_from_start=rclcpp::Duration::from_seconds(0.1);
        left_goal_msg.trajectory.points.push_back(point);

        auto send_goal_options=rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
        send_goal_options.goal_response_callback = 
            [this](const GoalHandleFJT::SharedPtr & goal_handle) {
                if (!goal_handle) {
                    RCLCPP_ERROR(this->get_logger(), "Trajectory goal rejected");
                } else {
                    RCLCPP_INFO(this->get_logger(), "Trajectory goal accepted");
                }
            };
        left_client_->async_send_goal(left_goal_msg,send_goal_options);
    }
    void send_trajectory_to_right()
    {
        if (!right_client_->wait_for_action_server(1s)) {
            RCLCPP_ERROR(this->get_logger(), "Dummy2 right action server not available");
            return;
        }
        auto right_goal_msg=FollowJointTrajectory::Goal();
        right_goal_msg.trajectory.joint_names=right_arm_joints;
        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.positions=std::vector<double>(current_right_arm.data(),current_right_arm.data()+6);
        point.time_from_start=rclcpp::Duration::from_seconds(0.1);
        right_goal_msg.trajectory.points.push_back(point);

        auto send_goal_options=rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
        send_goal_options.goal_response_callback = 
            [this](const GoalHandleFJT::SharedPtr & goal_handle) {
                if (!goal_handle) {
                    RCLCPP_ERROR(this->get_logger(), "Trajectory goal rejected");
                } else {
                    RCLCPP_INFO(this->get_logger(), "Trajectory goal accepted");
                }
            };
        right_client_->async_send_goal(right_goal_msg,send_goal_options);
    }

    void publish_joint_states() {
        auto msg = sensor_msgs::msg::JointState();
        msg.header.stamp = this->now();
        
        // 组装所有关节名称和位置
        msg.name.insert(msg.name.end(), left_arm_joints.begin(), left_arm_joints.end());
        msg.name.insert(msg.name.end(), left_hand_joints.begin(), left_hand_joints.end());
        //msg.name.push_back(left_hand_joint);
        msg.name.insert(msg.name.end(), right_arm_joints.begin(), right_arm_joints.end());
        msg.name.insert(msg.name.end(), right_hand_joints.begin(), right_hand_joints.end());
        //msg.name.push_back(right_hand_joint);
        
        msg.position.insert(msg.position.end(), current_left_arm.data(), current_left_arm.data()+6);
        msg.position.insert(msg.position.end(), current_left_hand.data(), current_left_hand.data()+2);
        //msg.position.push_back(current_left_hand);
        msg.position.insert(msg.position.end(), current_right_arm.data(), current_right_arm.data()+6);
        msg.position.insert(msg.position.end(), current_right_hand.data(), current_right_hand.data()+2);
        //msg.position.push_back(current_right_hand);
        
        joint_pub_->publish(msg);
    }
    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr left_client_;

    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr right_client_;

    Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_pub_;
    Subscription<arm_control::msg::TrajectoryPoint>::SharedPtr traj_sub_;
    Subscription<arm_control::msg::ControlCommand>::SharedPtr cmd_sub_;
    TimerBase::SharedPtr timer_;
    
    vector<string> left_arm_joints, right_arm_joints;
    vector<string> left_hand_joints, right_hand_joints;
    Eigen::VectorXd current_left_arm, current_right_arm;
    Eigen::Vector2d current_left_hand, current_right_hand;
    
    // 关节限制（与IK节点一致）
    vector<pair<double, double>> joint_limits = {
        {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI},
        {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI},
    };
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<ArmControllerNode>());
    rclcpp::shutdown();
    return 0;
}