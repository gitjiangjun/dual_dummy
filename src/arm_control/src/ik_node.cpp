#include "rclcpp/rclcpp.hpp"
#include "arm_control/msg/ik_result.hpp"
#include "arm_control/msg/control_command.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include<motionlib.h>
#include <Eigen/Dense>
#include <iostream>
#include <thread>
#include <sstream>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainiksolvervel_pinv.hpp>
#include <kdl/chainiksolverpos_nr.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>  // 添加这个头文件
#include <kdl/frames_io.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <urdf/model.h>

using namespace std;
using namespace rclcpp;
using namespace Eigen;
using namespace KDL;

class IKNode : public Node {
public:
    IKNode() : Node("ik_node") {
        // 获取参数
        std::string urdf_string = this->declare_parameter("robot_description", "");
        
        // 解析URDF
        urdf::Model model;
        if (!model.initString(urdf_string)) {
            RCLCPP_ERROR(this->get_logger(), "URDF parse failed");
            rclcpp::shutdown();
            return;
        }

        // 从URDF构建KDL树
        if (!kdl_parser::treeFromUrdfModel(model, kdl_tree_)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to construct KDL tree from URDF");
            rclcpp::shutdown();
        }

        // 初始化关节限制
        initializeJointLimits();

        // 初始化发布器和订阅器
        ik_pub_ = this->create_publisher<arm_control::msg::IKResult>("ik_result", 10);
        cmd_pub_ = this->create_publisher<arm_control::msg::ControlCommand>("control_command", 10);
        joint_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states", 10, bind(&IKNode::joint_callback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "IK node initialized. Enter commands:");
        RCLCPP_INFO(this->get_logger(), "  - Pose: pose [left/right] x y z rx ry rz");
        RCLCPP_INFO(this->get_logger(), "  - Gripper: gripper [left/right] [open/close]");
        RCLCPP_INFO(this->get_logger(), "  - Get Pose: get_pose [left/right]");
        RCLCPP_INFO(this->get_logger(), "  - Cooperation: coop [物体ID] [物体初始x y z rx ry rz] [物体目标x y z rx ry rz] [左臂抓取x y z rx ry rz] [右臂抓取x y z rx ry rz]");

        
        // 启动终端输入线程
        thread input_thread(&IKNode::terminal_input, this);
        input_thread.detach();
    }

private:
    KDL::Tree kdl_tree_;
    Eigen::VectorXd left_current = VectorXd::Zero(6);  // 6个关节
    Eigen::VectorXd right_current = VectorXd::Zero(6); // 6个关节

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

    KDL::Frame convert_to_kdl_frame(const Matrix4d& pose) {
        KDL::Frame frame;
        // 设置位置
        frame.p.x(pose(0,3));
        frame.p.y(pose(1,3));
        frame.p.z(pose(2,3));
        
        // 设置旋转矩阵
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                frame.M(i,j) = pose(i,j);
            }
        }
        return frame;
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

    IKSolution solve_ik(const string& arm, const Matrix4d& target_pose, const VectorXd& initial_angles) {
        IKSolution result;
        result.success = false;
        result.angles.resize(6); // 固定为6个关节
        
        try {
            // 获取运动学链
            KDL::Chain chain;
            string base_link = arm + "_base_link";
            string tip_link = arm + "_link6_1";
            
            if (!kdl_tree_.getChain(base_link, tip_link, chain)) {
                RCLCPP_ERROR(this->get_logger(), "Failed to get KDL chain for %s arm", arm.c_str());
                return result;
            }

            // 检查关节数量是否为6
            if (chain.getNrOfJoints() != 6) {
                RCLCPP_ERROR(this->get_logger(), "Chain for %s arm has %d joints (expected 6)", 
                           arm.c_str(), chain.getNrOfJoints());
                return result;
            }

            // 创建求解器
            ChainFkSolverPos_recursive fk_solver(chain);
            ChainIkSolverVel_pinv vel_ik_solver(chain);
            ChainIkSolverPos_NR_JL ik_solver(chain, joint_min,joint_max,fk_solver, vel_ik_solver, 150, 0.5*1e-2);

            // 设置初始关节位置
            KDL::JntArray q_init(chain.getNrOfJoints());
            for (size_t i = 0; i < chain.getNrOfJoints(); i++) {
                q_init(i) = initial_angles[i];
            }

            // 转换目标位姿到KDL格式
            KDL::Frame target_frame = convert_to_kdl_frame(target_pose);

            // 求解逆运动学
            KDL::JntArray q_out(chain.getNrOfJoints());
            int ret = ik_solver.CartToJnt(q_init, target_frame, q_out);
            
            if (ret >= 0) {
                result.success = true;
                for (size_t i = 0; i < 6; i++) {
                    result.angles[i] = std::fmod(q_out(i)+M_PI,2*M_PI)-M_PI;
                }
            } else {
                RCLCPP_WARN(this->get_logger(), "IK solver failed with error code: %d", ret);
            }
        } catch (const exception& e) {
            RCLCPP_ERROR(this->get_logger(), "IK solver exception: %s", e.what());
        }
        
        return result;
    }

    KDL::Frame getCurrentEndEffectorPose(const string& arm) {
        KDL::Chain chain;
        string base_link = arm + "_base_link";
        string tip_link = arm + "_link6_1";
        
        if (!kdl_tree_.getChain("base_plate", tip_link, chain)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to get KDL chain for %s arm", arm.c_str());
            return KDL::Frame();
        }

        ChainFkSolverPos_recursive fk_solver(chain);
        KDL::JntArray q(chain.getNrOfJoints());
        VectorXd current_angles = (arm == "left") ? left_current : right_current;
        for (size_t i = 0; i < chain.getNrOfJoints(); i++) {
            q(i) = current_angles[i];
        }

        KDL::Frame pose;
        int ret = fk_solver.JntToCart(q, pose);
        if (ret < 0) {
            RCLCPP_ERROR(this->get_logger(), "Forward kinematics solver failed for %s arm", arm.c_str());
        }
        return pose;
    }
    // 辅助函数：将机械臂移动到指定位姿
    void moveArmToPose(const std::string& arm, const Matrix4d& target_pose) {

        VectorXd initial_angles=(arm == "left")?left_current:right_current;

        KDL::Frame start_=getCurrentEndEffectorPose(arm);
        Matrix4d start_pose=Matrix4d::Identity();
        // 提取位置信息
        start_pose(0, 3) = start_.p.x();  // 平移 x
        start_pose(1, 3) = start_.p.y();  // 平移 y
        start_pose(2, 3) = start_.p.z();  // 平移 z

        // 提取旋转信息（3x3 矩阵）
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                start_pose(i, j) = start_.M(i, j);  // 旋转矩阵
            }
        }
        Matrix4d lo_start_pose=Convert_to_Arm(arm,start_pose);
        //转换到臂坐标系
        Eigen::Matrix4d lo_target_pose=Convert_to_Arm(arm,target_pose);
        std::vector<PathPoint> temp_j=cartesianLinearTrajectory(lo_start_pose,lo_target_pose,10,1);
        IKSolution sol;
        auto ik_msgs=arm_control::msg::IKResult();
        RCLCPP_INFO(this->get_logger(),"num of cartesia:%d",temp_j.size());
        for(int i=0;i<temp_j.size()-1;i++){
            sol = solve_ik(arm, temp_j[i+1].pose, initial_angles);
            if(sol.success){
                for (int i = 0; i < 6; i++) {
                    initial_angles[i] = sol.angles[i];//模拟逼近
                }
            } 
            RCLCPP_INFO(this->get_logger(),"%d /10 of ik",i);
        }
        //只要最后的结果
        if(sol.success){
            ik_msgs.success=sol.success;
            ik_msgs.arm_name=arm+"_arm";
            ik_msgs.joint_angles=sol.angles;
            ik_pub_->publish(ik_msgs);
            RCLCPP_INFO(this->get_logger(), "IK solved for %s: [%.3f, %.3f, %.3f, %.3f, %.2f, %.3f]", 
        arm.c_str(), sol.angles[0], sol.angles[1], sol.angles[2],sol.angles[3], sol.angles[4], sol.angles[5]);
            RCLCPP_INFO(this->get_logger(),"sleep before");
            rclcpp::sleep_for(std::chrono::seconds(5));
            RCLCPP_INFO(this->get_logger(),"sleep after");
        }else{
            RCLCPP_ERROR(this->get_logger(), "Failed to compute IK for %s arm", arm.c_str());
        }
    }
    // 辅助函数：执行抓取动作
    void executeGrasp(const std::string& arm) {
        auto msg = arm_control::msg::ControlCommand();
        msg.arm_name = arm + "_arm";
        msg.command_type = "gripper";
        msg.gripper_state = "open";
        cmd_pub_->publish(msg);
        rclcpp::sleep_for(std::chrono::seconds(2));  // 等待抓取完成
        msg.gripper_state="close";
        cmd_pub_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "Executing grasp for %s arm", arm.c_str());
        rclcpp::sleep_for(std::chrono::seconds(2));  // 等待抓取完成
    }
    // 辅助函数：同步执行双臂运动
    void executeSynchronizedMotion(const std::vector<PathPoint>& left_path, 
                                const std::vector<PathPoint>& right_path) {
        
        // 假设左右路径长度相同且时间戳匹配
        size_t path_length = left_path.size();
        // 计算时间差
        double dt=left_path[1].time-left_path[1].time;
        std::chrono::nanoseconds duration(static_cast<int64_t>(dt*1e9));

        std::vector<arm_control::msg::IKResult> joint_path(path_length);
        for (size_t i = 0; i < path_length; i++) {
            
            // 对左右臂同时求解并发布
            VectorXd left_initial = left_current;//在此时，left_current为离状态，没有其他节点引起更新，自己节点也没有那个能力更新
            VectorXd right_initial = right_current;
            
            IKSolution left_sol = solve_ik("left", left_path[i].pose, left_initial);
            IKSolution right_sol = solve_ik("right", right_path[i].pose, right_initial);
            
            if (left_sol.success && right_sol.success) {
                // 发布左臂关节角度
                auto arm_msg = arm_control::msg::IKResult();
                arm_msg.arm_name = "dual_arm";
                arm_msg.success = true;
                arm_msg.joint_angles.resize(12);
                for (int j = 0; j < 6; j++) arm_msg.joint_angles[j] = left_sol.angles[j];
                for (int j = 6; j < 12; j++) arm_msg.joint_angles[j] = right_sol.angles[j-6];
                
                joint_path[i]=arm_msg;
                
                // 更新当前角度,因为还没执行
                left_current = Map<VectorXd>(left_sol.angles.data(), 6);
                right_current = Map<VectorXd>(right_sol.angles.data(), 6);
            } else {
                RCLCPP_ERROR(this->get_logger(), "Failed to compute synchronized IK at path point %zu", i);
                break;
            }
        }
        for(int i=0;i<path_length;i++){
            ik_pub_->publish(joint_path[i]);//发送执行
            //rclcpp::sleep_for(duration);
            this_thread::sleep_for(chrono::duration<double>(0.1));
        }
    }
    // 处理双臂协同搬运命令
    void handleCooperativeManipulation(const std::string& object_id, 
                                    const Matrix4d& object_initial_pose,
                                    const Matrix4d& object_target_pose,
                                    const Matrix4d& left_grasp_pose,
                                    const Matrix4d& right_grasp_pose) {
        
        // 1. 双臂分别移动到抓取位姿（非同步）
        moveArmToPose("left", left_grasp_pose);
        moveArmToPose("right", right_grasp_pose);
        
        // 2. 执行抓取动作
        executeGrasp("left");
        executeGrasp("right");
        
        // 3. 生成物体路径（从初始位置到目标位置）
        int num_path_points = 20;  // 路径点数量
        double dt=0.1;
        auto object_path = cartesianLinearTrajectory(object_initial_pose, object_target_pose, num_path_points*dt,dt);
        
        // 4. 生成双臂路径
        std::vector<PathPoint> left_path=Convert_to_Arm_Path(object_path,"left",left_grasp_pose);
        std::vector<PathPoint> right_path=Convert_to_Arm_Path(object_path,"right",right_grasp_pose);

        // 5. 同步执行搬运
        executeSynchronizedMotion(left_path, right_path);
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
                
                // 发布结果
                moveArmToPose(arm,target_pose);
                
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
                
            } else if (cmd_type == "get_pose") {
                if (!(iss >> arm) || (arm != "left" && arm != "right")) {
                    RCLCPP_WARN(this->get_logger(), "Invalid get_pose format. Use: get_pose [left/right]");
                    continue;
                }
                KDL::Frame pose = getCurrentEndEffectorPose(arm);
                RCLCPP_INFO(this->get_logger(), "Current end effector pose for %s arm:", arm.c_str());
                RCLCPP_INFO(this->get_logger(), "Position: [%.2f, %.2f, %.2f]", pose.p.x(), pose.p.y(), pose.p.z());
                RCLCPP_INFO(this->get_logger(), "Rotation matrix:");
                for (int i = 0; i < 3; ++i) {
                    RCLCPP_INFO(this->get_logger(), "  [%.2f, %.2f, %.2f]", pose.M(i, 0), pose.M(i, 1), pose.M(i, 2));
                }
            }else if(cmd_type == "coop"){
                // 处理协同搬运命令
                string object_id;
                double x1, y1, z1, rx1, ry1, rz1;  // 物体初始位姿
                double x2, y2, z2, rx2, ry2, rz2;  // 物体目标位姿
                double lx, ly, lz, lrx, lry, lrz;  // 左臂抓取位姿
                double rx, ry, rz, rrx, rry, rrz;  // 右臂抓取位姿
                
                if (!(iss >> object_id >> x1 >> y1 >> z1 >> rx1 >> ry1 >> rz1 >>
                    x2 >> y2 >> z2 >> rx2 >> ry2 >> rz2 >>
                    lx >> ly >> lz >> lrx >> lry >> lrz >>
                    rx >> ry >> rz >> rrx >> rry >> rrz)) {
                    RCLCPP_WARN(this->get_logger(), "Invalid coop format.");
                    continue;
                }
                
                // 构建位姿矩阵
                Matrix4d object_initial_pose = pose_from_xyzrpy(x1, y1, z1, rx1, ry1, rz1);
                Matrix4d object_target_pose = pose_from_xyzrpy(x2, y2, z2, rx2, ry2, rz2);
                Matrix4d left_grasp_pose = pose_from_xyzrpy(lx, ly, lz, lrx, lry, lrz);
                Matrix4d right_grasp_pose = pose_from_xyzrpy(rx, ry, rz, rrx, rry, rrz);
                
                // 处理协同搬运
                handleCooperativeManipulation(object_id, object_initial_pose, object_target_pose, 
                                            left_grasp_pose, right_grasp_pose);
            } else if (cmd_type == "help") {
                RCLCPP_INFO(this->get_logger(), "Available commands:");
                RCLCPP_INFO(this->get_logger(), "  pose [left/right] x y z rx ry rz");
                RCLCPP_INFO(this->get_logger(), "  gripper [left/right] [open/close]");
                RCLCPP_INFO(this->get_logger(), "  get_pose [left/right]");
                RCLCPP_INFO(this->get_logger(), "  coop [物体ID] [物体初始x y z rx ry rz] [物体目标x y z rx ry rz] [左臂抓取x y z rx ry rz] [右臂抓取x y z rx ry rz]");
                RCLCPP_INFO(this->get_logger(), "  help (m) (rad)");
                
            } else {
                RCLCPP_WARN(this->get_logger(), "Unknown command: %s. Type 'help' for usage.", cmd_type.c_str());
            }
        }
    }
        // 关节限制参数
    KDL::JntArray joint_min, joint_max;
    // 初始化关节限制
    void initializeJointLimits() {
        // 假设我们有6个关节，根据实际机械臂修改这些值
        int num_joints = 6;
        
        // 初始化左右臂关节限制数组
        joint_min.resize(num_joints);
        joint_max.resize(num_joints);
        
        // 设置左臂关节限制（单位：弧度）
        joint_min(0) = -2*M_PI;  // 关节1最小值
        joint_max(0) = 2*M_PI;   // 关节1最大值
        joint_min(1) = -2*M_PI;  // 关节2最小值
        joint_max(1) = 2*M_PI;   // 关节2最大值
        joint_min(2) = -2*M_PI;  // 关节3最小值
        joint_max(2) = 2*M_PI;   // 关节3最大值
        joint_min(3) = -2*M_PI;  // 关节4最小值
        joint_max(3) = 2*M_PI;   // 关节4最大值
        joint_min(4) = -2*M_PI;  // 关节5最小值
        joint_max(4) = 2*M_PI;   // 关节5最大值
        joint_min(5) = -2*M_PI;  // 关节6最小值
        joint_max(5) = 2*M_PI;   // 关节6最大值

        
    }

    Publisher<arm_control::msg::IKResult>::SharedPtr ik_pub_;
    Publisher<arm_control::msg::ControlCommand>::SharedPtr cmd_pub_;
    Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<IKNode>());
    rclcpp::shutdown();
    return 0;
}
