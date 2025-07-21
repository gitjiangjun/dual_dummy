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
struct PathPoint{
    Eigen::Matrix4d pose;
    double time;
};

struct IKSolution {
    bool success;
    std::vector<double> angles;
};

// 关节空间五次多项式插值（改进后）
std::vector<TrajectoryPoint> jointSpaceTrajectory(
    const Eigen::VectorXd& q_start,
    const Eigen::VectorXd& q_end,
    double total_time,
    double dt,
    const std::vector<std::pair<double, double>>& joint_limits);


//笛卡尔轨迹
std::vector<PathPoint> cartesianLinearTrajectory(
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt);

Eigen::Matrix4d Convert_to_Arm(std::string arm,Eigen::Matrix4d T_gtarget);
//协调变换
std::vector<PathPoint> Convert_to_Arm_Path(const std::vector<PathPoint> Ob_Path,const std::string arm,const Eigen::Matrix4d T_gstart);

void saveJointTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename);
void saveCartesianTrajectoryToCSV(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename);

#endif // !MOTIONLIB
