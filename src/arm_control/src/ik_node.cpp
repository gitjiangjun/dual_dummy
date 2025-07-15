#include "rclcpp/rclcpp.hpp"
#include "arm_control/msg/ik_result.hpp"
#include "arm_control/msg/control_command.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "motionlib.h"
#include <Eigen/Dense>
#include <iostream>
#include <thread>
#include <sstream>

using namespace std;
using namespace rclcpp;
using namespace Eigen;

// 机械臂DH参数（根据实际机器人修改）
vector<ModifiedDHParameter> left_dh_params = {
    {0.096, 0, 0.1, 0},   // 关节1
    {0.0285, M_PI/2.0, 0.03448, M_PI/2.0}, // 关节2
    {0.02451, M_PI/2.0, 0.168, 0},    // 关节3
    {-0.01316, 0, 0.06247, -M_PI/2.0}, // 关节4
    {-0.1141, 0, 0, -M_PI/2.0}, // 关节5
    {-0.00148, M_PI, 0.00123, -M_PI/2.0}, // 关节6

};

vector<ModifiedDHParameter> right_dh_params = {
    {0.096, 0, 0.1, 0},   // 关节1
    {0.0285, M_PI/2.0, 0.03448, M_PI/2.0}, // 关节2
    {0.02451, M_PI/2.0, 0.168, 0},    // 关节3
    {-0.01316, 0, 0.06247, -M_PI/2.0}, // 关节4
    {-0.1141, 0, 0, -M_PI/2.0}, // 关节5
    {-0.00148, M_PI, 0.00123, -M_PI/2.0}, // 关节6

};

// 关节限制（弧度）
vector<pair<double, double>> joint_limits = {
    {-2.8, 2.8}, {-2.8, 2.8}, {-2.8, 2.8},
    {-2.8, 2.8}, {-2.8, 2.8}, {-2.8, 2.8},

};

class IKNode : public Node {
public:
    IKNode() : Node("ik_node") {
        ik_pub_ = this->create_publisher<arm_control::msg::IKResult>("ik_result", 10);
        cmd_pub_ = this->create_publisher<arm_control::msg::ControlCommand>("control_command", 10);
        joint_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states", 10, bind(&IKNode::joint_callback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "IK node initialized. Enter commands:");
        RCLCPP_INFO(this->get_logger(), "  - Pose: pose [left/right] x y z rx ry rz");
        RCLCPP_INFO(this->get_logger(), "  - Gripper: gripper [left/right] [open/close]");
        
        // 启动终端输入线程
        thread input_thread(&IKNode::terminal_input, this);
        input_thread.detach();
    }

private:
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

    Matrix4d pose_from_xyzrpy(double x, double y, double z, double rx, double ry, double rz) {
        Matrix4d T = Matrix4d::Identity();
        T.block<3,1>(0,3) << x, y, z;
        
        // RPY转旋转矩阵（ZYX顺序）
        AngleAxisd rz_rot(rz, Vector3d::UnitZ());
        AngleAxisd ry_rot(ry, Vector3d::UnitY());
        AngleAxisd rx_rot(rx, Vector3d::UnitX());
        T.block<3,3>(0,0) = (rz_rot * ry_rot * rx_rot).matrix();
        return T;
    }

    void terminal_input() {
        string line;
        while (rclcpp::ok() && getline(cin, line)) {
            istringstream iss(line);
            string cmd_type, arm;
            
            if (!(iss >> cmd_type)) {
                RCLCPP_WARN(this->get_logger(), "Invalid command. See help.");
                continue;
            }
            
            if (cmd_type == "pose") {
                // 处理位姿命令
                double x, y, z, rx, ry, rz;
                if (!(iss >> arm >> x >> y >> z >> rx >> ry >> rz)) {
                    RCLCPP_WARN(this->get_logger(), "Invalid pose format. Use: pose [left/right] x y z rx ry rz");
                    continue;
                }
                
                // 构建目标位姿
                Matrix4d target_pose = pose_from_xyzrpy(x, y, z, rx, ry, rz);
                VectorXd initial_angles(6);
                auto& dh_params = (arm == "left") ? left_dh_params : right_dh_params;
                int l_r = (arm == "left") ? -1 : 1;  // 区分左右臂基坐标
                
                // 获取初始角度
                initial_angles = (arm == "left") ? left_current : right_current;
                
                // 调用逆运动学求解
                Solution sol = inverseKinematics(
                    dh_params, initial_angles, target_pose, l_r,
                    joint_limits, 100, 1e-4, 0.1
                );
                
                // 发布结果
                arm_control::msg::IKResult msg;
                msg.arm_name = arm + "_arm";
                msg.success = sol.success;
                if (sol.success) {
                    msg.joint_angles.assign(sol.angles.data(), sol.angles.data()+6);
                    RCLCPP_INFO(this->get_logger(), "IK solved for %s: [%s]", 
                              arm.c_str(), format_joint_angles(sol.angles).c_str());
                } else {
                    RCLCPP_WARN(this->get_logger(), "IK failed for %s", arm.c_str());
                }
                ik_pub_->publish(msg);
                
            } else if (cmd_type == "gripper") {
                // 处理夹爪命令
                string state;
                if (!(iss >> arm >> state) || (state != "open" && state != "close")) {
                    RCLCPP_WARN(this->get_logger(), "Invalid gripper format. Use: gripper [left/right] [open/close]");
                    continue;
                }
                
                // 发布夹爪控制命令
                auto msg = arm_control::msg::ControlCommand();
                msg.arm_name = arm + "_arm";
                msg.command_type = "gripper";
                msg.gripper_state = state;
                cmd_pub_->publish(msg);
                RCLCPP_INFO(this->get_logger(), "Sending gripper command: %s %s", arm.c_str(), state.c_str());
                
            } else if (cmd_type == "help") {
                RCLCPP_INFO(this->get_logger(), "Available commands:");
                RCLCPP_INFO(this->get_logger(), "  pose [left/right] x y z rx ry rz");
                RCLCPP_INFO(this->get_logger(), "  gripper [left/right] [open/close]");
                RCLCPP_INFO(this->get_logger(), "  help");
                
            } else {
                RCLCPP_WARN(this->get_logger(), "Unknown command: %s. Type 'help' for usage.", cmd_type.c_str());
            }
        }
    }

    string format_joint_angles(const Eigen::VectorXd& angles) {
        ostringstream oss;
        oss.precision(2);
        oss << fixed;
        for (int i = 0; i < angles.size(); i++) {
            oss << (i > 0 ? ", " : "") << angles[i];
        }
        return oss.str();
    }

    Publisher<arm_control::msg::IKResult>::SharedPtr ik_pub_;
    Publisher<arm_control::msg::ControlCommand>::SharedPtr cmd_pub_;
    Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub_;
    VectorXd left_current = VectorXd::Zero(6);
    VectorXd right_current = VectorXd::Zero(6);
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<IKNode>());
    rclcpp::shutdown();
    return 0;
}