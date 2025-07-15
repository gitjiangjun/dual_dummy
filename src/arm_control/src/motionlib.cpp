/*这是一个特定的7自由度的机械臂的基础代码库，包含了一些基础的结构体和工具函数，用来协助智能体完善和提升这个7自由度机械臂相关的代码。有可能存在错误*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include"motionlib.h"

// 计算所有关节的变换矩阵、位置和z轴
std::vector<Frame> computeFrames(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& joint_angles ,const int& l_r) {
    //修改基座位姿
    double rotation_angle = 0;//-M_PI / 2.0;
    Eigen::AngleAxisd rotation(rotation_angle, Eigen::Vector3d::UnitX());
    Eigen::Translation3d translation(l_r*0.3, -0.2, 0.025);//l_r左负右正
    Eigen::Matrix4d T_base = (translation * rotation).matrix();

    std::vector<Frame> frames;
    Eigen::Matrix4d T = T_base*Eigen::Matrix4d::Identity();

    for (size_t i = 0; i < dh_params.size(); ++i) {
        const ModifiedDHParameter& param = dh_params[i];
        double theta = joint_angles[i] + param.theta;
        double c_theta = cos(theta);
        double s_theta = sin(theta);
        double c_alpha = cos(param.alpha);
        double s_alpha = sin(param.alpha);

        Eigen::Matrix4d T_i;
        T_i <<  c_theta,   -s_theta*c_alpha,    s_theta*s_alpha,    param.a*c_theta,
                s_theta,    c_theta*c_alpha,   -c_theta*s_alpha,    param.a*s_theta,
                 0,       s_alpha,       c_alpha,        param.d,
                 0,        0,        0,             1;

        T *= T_i;

        Frame frame;
        frame.transform = T;
        frame.position = T.block<3, 1>(0, 3);
        frame.z_axis = T.block<3, 1>(0, 2).normalized();
        frames.push_back(frame);
    }
    return frames;
}

// 正运动学函数，使用改进的 DH 参数计算末端执行器的位置和姿态
Eigen::Matrix4d forwardKinematics(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& joint_angles, const int & l_r) {

    auto frames = computeFrames(dh_params, joint_angles,l_r);
    return frames.back().transform;
}

// 计算空间雅可比矩阵
Eigen::MatrixXd jacobian(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& joint_angles, const int& l_r) {
    auto frames = computeFrames(dh_params, joint_angles,l_r);
    Eigen::MatrixXd J(6, dh_params.size());
    Eigen::Vector3d end_effector_pos = frames.back().position;

    for (size_t i = 0; i < dh_params.size(); ++i) {
        const Frame& frame = frames[i];
        J.block<3, 1>(0, i) = frame.z_axis.cross(end_effector_pos - frame.position);
        J.block<3, 1>(3, i) = frame.z_axis;
    }
    return J;
}

// 数值雅可比验证函数
Eigen::MatrixXd numericalJacobian(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& joint_angles,
    const int& l_r,
    const std::vector<std::pair<double, double>>& joint_limits,
    double delta) {
    const size_t n = joint_angles.size();
    Eigen::MatrixXd J_num(6, n);
    const Eigen::Matrix4d T0 = forwardKinematics(dh_params, joint_angles,l_r);
    const Eigen::Vector3d p0 = T0.block<3, 1>(0, 3);
    const Eigen::Quaterniond q0(T0.block<3, 3>(0, 0));

    for (int i = 0; i < n; ++i) {
        Eigen::VectorXd angles_plus = joint_angles;
        angles_plus[i] = angles_plus[i] + delta;

        const Eigen::Matrix4d T_plus = forwardKinematics(dh_params, angles_plus,l_r);
        const Eigen::Vector3d p_plus = T_plus.block<3, 1>(0, 3);
        const Eigen::Quaterniond q_plus(T_plus.block<3, 3>(0, 0));

        // 位置导数
        J_num.block<3, 1>(0, i) = (p_plus - p0) / delta;

        // 姿态导数
        Eigen::Quaterniond dq = q_plus * q0.conjugate();
        if (dq.w() < 0) dq.coeffs() *= -1;
        Eigen::AngleAxisd aa(dq);
        if (aa.angle() < 1e-8) aa = Eigen::AngleAxisd(0, aa.axis());
        J_num.block<3, 1>(3, i) = aa.axis() * aa.angle() / delta;
    }
    return J_num;
}
// 新增位姿误差计算函数
Eigen::VectorXd computePoseError(const Eigen::Matrix4d& current_pose,
    const Eigen::Matrix4d& target_pose) {
    // 位置误差
    Eigen::Vector3d position_error = target_pose.block<3, 1>(0, 3) - current_pose.block<3, 1>(0, 3);
    // 处理极小位置误差（避免噪声）
    if (position_error.norm() < 1e-8) {
        position_error.setZero();
    }

    // 姿态误差（四元数）
    Eigen::Quaterniond q_current(current_pose.block<3, 3>(0, 0));
    Eigen::Quaterniond q_target(target_pose.block<3, 3>(0, 0));

    // 确保四元数方向一致
    if (q_current.dot(q_target) < 0) {
        q_target.coeffs() *= -1;
    }
    Eigen::Quaterniond q_error = q_target * q_current.conjugate();

    // 处理小角度情况（避免轴方向突变）
    Eigen::Vector3d orientation_error;
    if (q_error.norm() < 1e-8) {
        // 当角度极小时，直接使用四元数虚部近似旋转矢量
        orientation_error = 2 * q_error.vec();  // 2 * (x,y,z)
    }
    else {
        // 常规情况：使用轴角表示
        Eigen::AngleAxisd aa_error(q_error);
        orientation_error = aa_error.axis() * aa_error.angle();
    }

    // 组合误差向量
    Eigen::VectorXd error(6);
    error << position_error, orientation_error;
    return error;
}

//逆运动学求解函数（使用 SVD 和自适应阻尼）
Solution inverseKinematics(const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::VectorXd& initial_angles,
    const Eigen::Matrix4d& target_pose,
    const int& l_r,
    const std::vector<std::pair<double, double>>& joint_limits,
    int max_iterations,
    double tolerance,
    double initial_damping) {
    //结果
    Solution final = { initial_angles,false };

    //Eigen::VectorXd initial_angles(7);
    //initial_angles << M_PI/4,-M_PI/4,M_PI/4,-M_PI/4,M_PI/4,-M_PI/4,M_PI/4;
    
    size_t num_joints = dh_params.size();
    Eigen::VectorXd angles = initial_angles;
    Eigen::VectorXd prev_angles = angles;
    double damping = initial_damping;
    bool converged = false;

    
    //更新位姿
    Eigen::Matrix4d current_pose = forwardKinematics(dh_params, angles,l_r);
    // 计算误差
    Eigen::VectorXd error = computePoseError(current_pose, target_pose);
    double error_norm = error.squaredNorm();
    double prev_error_norm = error_norm;
    Eigen::Vector3d positon_error = error.head<3>();
    Eigen::Vector3d orientation_error = error.tail<3>();
    
    double positon_tolerance = tolerance*tolerance;
    double orientation_tolerance = 100*tolerance*tolerance;//(10*tolerance)^2
    // 检查
    if ((positon_error.squaredNorm() < positon_tolerance)&&(orientation_error.squaredNorm()<orientation_tolerance)) {
        //converged = true;
        final.angles = angles;
        final.success = true;
        //std::cout << "Converged in " << iter << " iterations." << ", error norm: " << error.norm() << ",used damping:" << damping << std::endl;
        return final;
    }

    for (int iter = 1; iter <= max_iterations; ++iter) {
        // 计算雅可比矩阵
        Eigen::MatrixXd J = jacobian(dh_params, angles,l_r);

        // SVD 分解
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(J, Eigen::ComputeThinU | Eigen::ComputeThinV);
        Eigen::VectorXd singular_values = svd.singularValues();

        // 在逆运动学的 SVD 后添加
        double min_singular_value = singular_values.minCoeff();
        if (min_singular_value < 1e-6) {
            std::cout << "警告：接近奇异位形，最小奇异值: " << min_singular_value << std::endl;
            damping = std::max(damping, 0.1); // 增大阻尼
            /*
            double epsilon = 1e-6;
            singular_values = (singular_values.array() > epsilon)
                .select(singular_values, epsilon);
            */
        }

        Eigen::MatrixXd J_pinv = svd.matrixV() *
            (singular_values.array() / (singular_values.array().square() + damping * damping)).matrix().asDiagonal() *
            svd.matrixU().transpose();
        // 计算初步delta_theta
        Eigen::VectorXd delta_theta = J_pinv * error;




        angles += (delta_theta);
        /*
        if (angles.cwiseAbs().maxCoeff() > M_PI) {
            std::cout << "超界" << std::endl;
            //angles = prev_angles;
            //damping *= 5;
            //continue;
        }*/
        for (int i = 0; i < num_joints; ++i) {
            angles[i] = std::fmod(angles[i] + M_PI, 2 * M_PI) - M_PI;
            angles[i] = std::clamp(angles[i], joint_limits[i].first, joint_limits[i].second);
        }

        //更新位姿
        current_pose = forwardKinematics(dh_params, angles,l_r);
        // 计算误差
        error = computePoseError(current_pose, target_pose);
        error_norm = error.squaredNorm();
        Eigen::Vector3d positon_error = error.head<3>();
        Eigen::Vector3d orientation_error = error.tail<3>();
        // 收敛检查
        if ((positon_error.squaredNorm() < positon_tolerance) && (orientation_error.squaredNorm() < orientation_tolerance)) {
            converged = true;
            final.angles = angles;
            final.success = true;
            //std::cout << "Converged in " << iter << " iterations." << ", error norm: " << error.norm() << ",used damping:" << damping << std::endl;
            return final;
        }
        // 在逆运动学中增加详细调试信息
        if (iter % 60 == 0) {
            std::cout << "Iter " << iter
                << " Error: " << error.norm()
                << " Damping: " << damping
                << " Max Joint Delta: " << delta_theta.cwiseAbs().maxCoeff()
                << std::endl;
        }
        // 动态调整阻尼
        // 修改后的阻尼调整逻辑
        if (error_norm < prev_error_norm) {
            damping *= 0.80;  // 误差减小，降低阻尼
            //prev_angles = angles;
        }
        else {
            damping *= 5;  // 误差增大，增加阻尼
            //angles = prev_angles;
        }
        damping = std::clamp(damping, 1e-5,0.1);  // 限制阻尼范围，比较常规的范围
        prev_error_norm = error_norm;

    }
    if (!converged) {
        std::cerr << "警告：逆运动学未收敛" << std::endl;
    }
    return final;
}

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

std::vector<TrajectoryPoint> cartesianLinearTrajectoryForPlotting(
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt) {

    int num_points = static_cast<int>(std::ceil(total_time / dt)) + 1;
    if (num_points < 2) num_points = 2;
    double adjusted_dt = total_time / (num_points - 1);

    std::vector<TrajectoryPoint> trajectory;
    trajectory.reserve(num_points);

    Eigen::Vector3d start_pos = start_pose.block<3, 1>(0, 3);
    Eigen::Vector3d end_pos = end_pose.block<3, 1>(0, 3);
    Eigen::Vector3d delta_pos = end_pos - start_pos;


    for (int i = 0; i < num_points; ++i) {
        double t = i * adjusted_dt;

        double tau = t / total_time;  // 归一化时间 [0,1]

        // 计算s(t)及其导数 --------------------------------
        const double tau2 = tau * tau;
        const double tau3 = tau2 * tau;
        const double tau4 = tau3 * tau;
        const double tau5 = tau4 * tau;

        // s(t) = 10*tau^3 - 15*tau^4 + 6*tau^5
        const double s = 10 * tau3 - 15 * tau4 + 6 * tau5;

        // ds/dt = (30*tau^2 - 60*tau^3 + 30*tau^4)/T
        const double ds_dt = (30 * tau2 - 60 * tau3 + 30 * tau4) / total_time;

        // d2s/dt2 = (60*tau - 180*tau2 + 120*tau3)/T^2
        const double d2s_dt2 = (60 * tau - 180 * tau2 + 120 * tau3) / (total_time * total_time);
        // 位置插值
        Eigen::Vector3d current_pos = start_pos + s * delta_pos;

        TrajectoryPoint point;
        point.time = t;
        point.positions = current_pos;
        point.velocities = ds_dt * delta_pos;
        point.accelerations = d2s_dt2 * delta_pos;
        trajectory.push_back(point);
    }
    return trajectory;
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

// 笛卡尔直线规划（机械臂用）
/*
std::vector<TrajectoryPoint> cartesianLinearTrajectory(
    const std::vector<ModifiedDHParameter>& dh_params,
    const Eigen::Matrix4d& start_pose,
    const Eigen::Matrix4d& end_pose,
    double total_time,
    double dt,
    const std::vector<std::pair<double, double>>& joint_limits,
    const Eigen::VectorXd& initial_angles) {

    double j_max = 2.0;     // 最大加加速度
    double a_max = 1.0;     // 最大加速度
    double v_max = 0.5;     // 最大速度

    int num_joints = static_cast<int>(joint_limits.size());
    int num_points = static_cast<int>(std::ceil(total_time / dt)) + 1;
    if (num_points < 2) num_points = 2;
    double adjusted_dt = total_time / (num_points - 1);  // 调整后的实际步长
    std::vector<TrajectoryPoint> trajectory;
    Eigen::VectorXd prev_angles = initial_angles;

    // 路径离散化
    for (int i = 0; i < num_points; ++i) {
        double t = i * adjusted_dt;
        // 使用S型曲线比例
        double ratio = sCurveRatio(t, total_time, j_max, a_max, v_max);

        // 线性插值位姿
        Eigen::Vector3d start_pos = start_pose.block<3, 1>(0, 3);
        Eigen::Vector3d end_pos = end_pose.block<3, 1>(0, 3);
        Eigen::Vector3d interp_pos = start_pos + ratio * (end_pos - start_pos);

        Eigen::Matrix3d start_rot = start_pose.block<3, 3>(0, 0);
        Eigen::Matrix3d end_rot = end_pose.block<3, 3>(0, 0);
        Eigen::Quaterniond q_start(start_rot);
        Eigen::Quaterniond q_end(end_rot);
        // 计算四元数插值前检查点积
        if (q_start.dot(q_end) < 0) {
            q_end.coeffs() *= -1; // 保证最短路径
        }
        Eigen::Quaterniond interp_rot = q_start.slerp(ratio, q_end);
        interp_rot.normalize();

        Eigen::Matrix4d target_pose = Eigen::Matrix4d::Identity();
        target_pose.block<3, 3>(0, 0) = interp_rot.toRotationMatrix();
        target_pose.block<3, 1>(0, 3) = interp_pos;
        // 逆运动学求解
        //std::cout << "笛卡尔正在处理第" << i << "个点" << std::endl;
        //std::cout << "ratio:\n" << target_pose << std::endl;
        //std::cout << "当前角度：\n" << prev_angles/M_PI*180 << std::endl;
        Solution solution = inverseKinematics(
            dh_params,
            prev_angles,
            target_pose,
            joint_limits,
            100,
            1e-4,
            1.0
        );
        if (!solution.success) {
            solution = inverseKinematics(dh_params, initial_angles, target_pose, joint_limits, 100, 1e-4, 1.0);
            if (!solution.success) {
                std::cout << "笛卡尔规划失败" << std::endl;
                break;
            }
        }
        // 更新轨迹点
        TrajectoryPoint point;
        point.time = t;
        point.positions = solution.angles;
        trajectory.push_back(point);
        prev_angles = solution.angles;
    }

    if (trajectory.size() <= 3) {
        std::cout << "轨迹错误" << std::endl;
        return trajectory;
    }
    // 修改后的速度计算
    for (size_t i = 0; i < trajectory.size(); ++i) {
        if (i == 0) {
            trajectory[i].velocities = (trajectory[1].positions - trajectory[0].positions) / adjusted_dt;
        }
        else if (i == trajectory.size() - 1) {
            trajectory[i].velocities = (trajectory[i].positions - trajectory[i - 1].positions) / adjusted_dt;
        }
        else {
            trajectory[i].velocities = (trajectory[i + 1].positions - trajectory[i - 1].positions) / (2 * adjusted_dt);
        }
    }
    // 加速度计算同理
    // 在笛卡尔轨迹函数中添加加速度计算
    for (size_t i = 0; i < trajectory.size(); ++i) {
        if (i == 0 || i == trajectory.size() - 1) {
            trajectory[i].accelerations = Eigen::VectorXd::Zero(num_joints);
        }
        else {
            trajectory[i].accelerations = (trajectory[i + 1].velocities - trajectory[i - 1].velocities) / (2 * adjusted_dt);
        }
    }
    return trajectory;
}*/