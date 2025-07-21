/*这是一个特定的7自由度的机械臂的基础代码库，包含了一些基础的结构体和工具函数，用来协助智能体完善和提升这个7自由度机械臂相关的代码。有可能存在错误*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include"motionlib.h"


// 关节空间五次多项式插值（改进后）
std::vector<TrajectoryPoint> jointSpaceTrajectory(
    const Eigen::VectorXd& q_start,
    const Eigen::VectorXd& q_end,
    double total_time,
    double dt,
    const std::vector<std::pair<double, double>>& joint_limits) {

    int num_joints = static_cast<int>(joint_limits.size());
    int num_points = static_cast<int>(std::ceil(total_time / dt)) + 1;
    if (num_points < 2) num_points = 2; // 至少两个点
    double adjusted_dt = total_time / (num_points - 1); // 调整后的时间步长

    std::vector<TrajectoryPoint> trajectory;
    trajectory.reserve(num_points);

    Eigen::VectorXd D = q_end - q_start;

    // 五次多项式系数计算
    Eigen::VectorXd a0 = q_start;
    Eigen::VectorXd a1 = Eigen::VectorXd::Zero(num_joints);
    Eigen::VectorXd a2 = Eigen::VectorXd::Zero(num_joints);
    Eigen::VectorXd a3 = 10.0 * D;
    Eigen::VectorXd a4 = -15.0 * D;
    Eigen::VectorXd a5 = 6.0 * D;

    for (int i = 0; i < num_points; ++i) {
        double t = i * adjusted_dt;
        double tau = t / total_time;

        TrajectoryPoint point;
        point.time = t;

        // 五次多项式位置计算
        point.positions = a0
            + a3 * std::pow(tau, 3)
            + a4 * std::pow(tau, 4)
            + a5 * std::pow(tau, 5);

        // 速度计算（导数）
        point.velocities = 3.0 * a3 * std::pow(tau, 2)
            + 4.0 * a4 * std::pow(tau, 3)
            + 5.0 * a5 * std::pow(tau, 4);
        point.velocities /= total_time;

        // 加速度计算（二阶导数）
        point.accelerations = 6.0 * a3 * tau
            + 12.0 * a4 * std::pow(tau, 2)
            + 20.0 * a5 * std::pow(tau, 3);
        point.accelerations /= (total_time * total_time);

        // 关节限位检查
        for (int j = 0; j < num_joints; ++j) {
            double original_pos = point.positions[j];
            point.positions[j] = std::clamp(original_pos, joint_limits[j].first, joint_limits[j].second);
            if (point.positions[j] != original_pos) {
                point.velocities[j] = 0.0;
                point.accelerations[j] = 0.0;
            }
        }

        trajectory.push_back(point);
    }
    return trajectory;
}

//笛卡尔轨迹
std::vector<PathPoint> cartesianLinearTrajectory(
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt) {

    int num_points = static_cast<int>(std::ceil(total_time / dt)) + 1;
    if (num_points < 2) num_points = 2;
    double adjusted_dt = total_time / (num_points - 1);

    std::vector<PathPoint> trajectory;
    trajectory.reserve(num_points);

    //位置提取
    Eigen::Vector3d start_pos = start_pose.block<3, 1>(0, 3);
    Eigen::Vector3d end_pos = end_pose.block<3, 1>(0, 3);
    Eigen::Vector3d delta_pos = end_pos - start_pos;
    //位姿提取
    Eigen::Matrix3d start_rot = start_pose.block<3, 3>(0, 0);
    Eigen::Matrix3d end_rot = end_pose.block<3, 3>(0, 0);
    Eigen::Quaterniond q_start(start_rot);
    Eigen::Quaterniond q_end(end_rot);
    // 计算四元数插值前检查点积
    if (q_start.dot(q_end) < 0) {
        q_end.coeffs() *= -1; // 保证最短路径
    }


    for (int i = 0; i < num_points; ++i) {
        double t = i * adjusted_dt;

        double tau = t / total_time;  // 归一化时间 [0,1]
       
        // 位置插值
        Eigen::Vector3d interp_pos = start_pos + tau * delta_pos;
        //位姿
        Eigen::Quaterniond interp_quat = q_start.slerp(tau, q_end);

        Eigen::Matrix4d current_pose=Eigen::Matrix4d::Identity();
        current_pose.block<3,1>(0,3)=interp_pos;
        current_pose.block<3,3>(0,0)=interp_quat.toRotationMatrix();

        PathPoint point;
        point.time = t;
        point.pose=current_pose;
        trajectory.push_back(point);
    }
    return trajectory;
}
//单个全局/局部转换
Eigen::Matrix4d Convert_to_Arm(std::string arm,Eigen::Matrix4d T_gtarget){
    //基座位姿
    Eigen::Matrix4d T_base=Eigen::Matrix4d::Identity();
    int b=(arm=="left")?-1:1;
    T_base(0,3)=b*0.3;T_base(1,3)=-0.2;T_base(2,3)= 0.0;

    Eigen::Matrix4d T_ltarget=T_base.inverse()*T_gtarget;
    return T_ltarget;
}

//协调变换
std::vector<PathPoint> Convert_to_Arm_Path(const std::vector<PathPoint> Ob_Path,const std::string arm,const Eigen::Matrix4d T_gstart){
    //基座位姿
    Eigen::Matrix4d T_base=Eigen::Matrix4d::Identity();
    int b=(arm=="left")?-1:1;
    T_base(0,3)=b*0.3;T_base(1,3)=-0.2;T_base(2,3)= 0.0;

    //全局坐标系下位姿传递
    std::vector<PathPoint> G_Path(Ob_Path.size());
    G_Path[0].pose=T_gstart;
    G_Path[0].time=Ob_Path[0].time;
    PathPoint G_point;
    for(int i=0;i<Ob_Path.size()-1;i++){
        G_point.pose=Ob_Path[i+1].pose*Ob_Path[i].pose.inverse()*G_Path[i].pose;
        G_point.time=Ob_Path[i+1].time;
        G_Path[i+1]=G_point;
    }
    //解算到局部坐标系Local_Path
    std::vector<PathPoint> L_path(G_Path.size());
    for(int i=0;i<G_Path.size();i++){
        L_path[i].pose=T_base.inverse()*G_Path[i].pose;
        L_path[i].time=G_Path[i].time;
    }
    return L_path;
}

// 保存关节轨迹到CSV
void saveJointTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    int num_joints = trajectory[0].positions.size();

    // 写表头
    file << "time";
    for (int i = 0; i < num_joints; ++i) file << ",pos" << i;
    for (int i = 0; i < num_joints; ++i) file << ",vel" << i;
    for (int i = 0; i < num_joints; ++i) file << ",acc" << i;
    file << "\n";

    // 写数据
    file.precision(5);
    file << std::fixed;
    for (const auto& pt : trajectory) {
        file << pt.time;
        for (double p : pt.positions) file << "," << p;
        for (double v : pt.velocities) file << "," << v;
        for (double a : pt.accelerations) file << "," << a;
        file << "\n";
    }
    file.close();
}

// 保存笛卡尔轨迹到CSV（假设 pos0-pos2 是 X,Y,Z； vel0-vel2 是 vx,vy,vz）
void saveCartesianTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    int num_joints = trajectory[0].positions.size();

    // 表头
    file << "time,X,Y,Z,Vx,Vy,Vz,Ax,Ay,Az\n";

    // 写数据（只写前3个位置和速度作为 XYZ 和 VX/VY/VZ）    // 数据（假设 pos0~2 是 XYZ，vel0~2 是 VX~VZ）
    file.precision(5);
    file << std::fixed;
    for (const auto& pt : trajectory) {
        file << pt.time;
        for (int i = 0; i < 3; ++i) file << "," << pt.positions[i];
        for (int i = 0; i < 3; ++i) file << "," << pt.velocities[i];
        for (int i = 0; i < 3; ++i) file << "," << pt.accelerations[i];
        file << "\n";
    }
    file.close();
}
