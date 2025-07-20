from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import OpaqueFunction, LogInfo
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
import os

def launch_setup(context, *args, **kwargs):
    try:
        # 获取绝对路径
        urdf_path = PathJoinSubstitution([
            FindPackageShare('dummy2_description'),
            'urdf',
            'dual_dummy.urdf'
        ]).perform(context)

        # 验证文件存在性
        if not os.path.exists(urdf_path):
            return [LogInfo(msg=f"[ERROR] URDF file not found: {urdf_path}")]

        # 读取URDF内容（指定UTF-8编码）
        with open(urdf_path, 'r', encoding='utf-8') as f:
            robot_desc = f.read().strip()

        if not robot_desc:
            return [LogInfo(msg="[ERROR] Empty URDF content")]

        return [
            Node(
                package='arm_control',
                executable='ik_node',
                name='ik_node',
                parameters=[{
                    'robot_description': robot_desc,
                    'use_sim_time': False
                }],
                output='screen',  # 建议添加以便查看日志
                emulate_tty=True,  # 新增这行
                prefix=['xterm -e']
            )
        ]

    except Exception as e:
        return [LogInfo(msg=f"[ERROR] Launch failed: {str(e)}")]

def generate_launch_description():
    return LaunchDescription([
        OpaqueFunction(function=launch_setup)
    ])
