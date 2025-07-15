#ifndef MOTIONLIB
#define MOTIONLIB
#include<vector>
#include <Eigen/Dense>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI

// 标准的 DH 参数结构体
struct ModifiedDHParameter {
    double d;     // d_{i-1}
    double theta; // theta_{i-1}
    double a;      // a_i
    double alpha;  // alpha_i
};
//每个关节的信息
struct Frame {
    Eigen::Matrix4d transform;
    Eigen::Vector3d position;
    Eigen::Vector3d z_axis;
};
// 轨迹点结构体（新增）
struct TrajectoryPoint {
    double time;
    Eigen::VectorXd positions;
    Eigen::VectorXd velocities;
    Eigen::VectorXd accelerations;
};

struct Solution {
    Eigen::VectorXd angles;
    bool success;
};
// 计算所有关节的变换矩阵、位置和z轴
std::vector<Frame> computeFrames(const std::vector<ModifiedDHParameter>& dh_params, const Eigen::VectorXd& joint_angles,const int& l_r);
// 正运动学函数，使用改进的 DH 参数计算末端执行器的位置和姿态
Eigen::Matrix4d forwardKinematics(const std::vector<ModifiedDHParameter>& dh_params, const Eigen::VectorXd& joint_angles,const int& l_r);
// 计算空间雅可比矩阵
Eigen::MatrixXd jacobian(const std::vector<ModifiedDHParameter>& dh_params, const Eigen::VectorXd& joint_angles,const int& l_r);
// 数值雅可比验证函数
Eigen::MatrixXd numericalJacobian(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& joint_angles,
    const int& l_r,
    const std::vector<std::pair<double, double>>& joint_limits,
    double delta = 1e-6);
//逆运动学求解函数（使用 SVD 和自适应阻尼）
Solution inverseKinematics(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& initial_angles,
    const Eigen::Matrix4d& target_pose,
    const int& l_r,
    const std::vector<std::pair<double, double>>& joint_limits,
    int max_iterations = 50,
    double tolerance = 1e-4,
    double initial_damping = 1e-2);
// 关节空间五次多项式插值（改进后）
std::vector<TrajectoryPoint> jointSpaceTrajectory(
    const Eigen::VectorXd& q_start,
    const Eigen::VectorXd& q_end,
    double total_time,
    double dt,
    const std::vector<std::pair<double, double>>& joint_limits);

// 笛卡尔直线规划（机械臂用）
std::vector<TrajectoryPoint> cartesianLinearTrajectory(
    const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt,
    const std::vector<std::pair<double, double>>& joint_limits,
    const Eigen::VectorXd& initial_angles);

//绘图用
std::vector<TrajectoryPoint> cartesianLinearTrajectoryForPlotting(
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt);

void saveJointTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename);
void saveCartesianTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename);

#endif // !MOTIONLIB
