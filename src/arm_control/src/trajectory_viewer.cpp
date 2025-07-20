#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "arm_control/msg/trajectory_point.hpp"
#include "motionlib.h"
#include <Eigen/Dense>

using namespace std;
using namespace rclcpp;

class TrajectoryViewer : public Node {
public:
    TrajectoryViewer() : Node("trajectory_viewer") {
        marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>(
            "visualization_marker", 10);
        
        traj_sub_ = this->create_subscription<arm_control::msg::TrajectoryPoint>(
            "trajectory_point", 10, bind(&TrajectoryViewer::traj_callback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "Trajectory viewer initialized");
    }

private:
    void traj_callback(const arm_control::msg::TrajectoryPoint::SharedPtr msg) {
        // 只处理左臂轨迹（可扩展到右臂）
        if (msg->arm_name != "left_arm") return;
        
        // 将关节角度转换为末端位姿
        Eigen::VectorXd joint_angles(6);
        for (int i = 0; i < 6; i++) joint_angles[i] = msg->positions[i];
        
        Eigen::Matrix4d pose = Eigen::Matrix4d::Identity();//forwardKinematics(left_dh_params, joint_angles, 1);
        Eigen::Vector3d position = pose.block<3, 1>(0, 3);
        
        // 创建可视化标记
        auto marker = visualization_msgs::msg::Marker();
        marker.header.frame_id = "base_plate";
        marker.header.stamp = this->now();
        marker.ns = "trajectory";
        marker.id = next_marker_id++;
        marker.type = visualization_msgs::msg::Marker::SPHERE;
        marker.action = visualization_msgs::msg::Marker::ADD;
        
        marker.pose.position.x = position[0];
        marker.pose.position.y = position[1];
        marker.pose.position.z = position[2];
        
        marker.scale.x = 0.01;
        marker.scale.y = 0.01;
        marker.scale.z = 0.01;
        
        // 按时间改变颜色（从红到绿）
        double ratio = std::min(1.0, msg->time_from_start / 5.0);
        marker.color.r = 1.0 - ratio;
        marker.color.g = ratio;
        marker.color.b = 0.0;
        marker.color.a = 1.0;
        
        marker.lifetime = rclcpp::Duration::from_seconds(30.0);
        marker_pub_->publish(marker);
    }

    Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
    Subscription<arm_control::msg::TrajectoryPoint>::SharedPtr traj_sub_;
    int next_marker_id = 0;
    
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<TrajectoryViewer>());
    rclcpp::shutdown();
    return 0;
}