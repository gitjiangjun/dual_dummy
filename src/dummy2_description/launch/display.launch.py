from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import os

def launch_setup(context, *args, **kwargs):
    # 获取参数值
    urdf_filename = LaunchConfiguration('urdf_filename').perform(context)
    use_rviz = LaunchConfiguration('use_rviz').perform(context)
    
    # 构建URDF文件路径
    dummy2_description_path = FindPackageShare('dummy2_description').find('dummy2_description')
    urdf_path = os.path.join(dummy2_description_path, 'urdf', urdf_filename)
    
    # 定义节点列表
    nodes = [
        # 1. 机器人状态发布器
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            arguments=[urdf_path]  # 直接传递字符串路径
        ),
        
        # 2. 关节状态发布器（已注释，避免冲突）
        # Node(
        #     package='joint_state_publisher_gui',
        #     executable='joint_state_publisher_gui',
        #     name='joint_state_publisher_gui',
        #     output='screen'
        # )
    ]
    
    # 3. 可选：启动RViz
    if use_rviz.lower() == 'true':
        nodes.append(
            Node(
                package='rviz2',
                executable='rviz2',
                name='rviz2',
                output='screen'
            )
        )
    
    return nodes

def generate_launch_description():
    return LaunchDescription([
        # 声明启动参数
        DeclareLaunchArgument(
            'urdf_filename',
            default_value='dual_dummy.urdf',
            description='URDF filename'
        ),
        DeclareLaunchArgument(
            'use_rviz',
            default_value='true',
            description='Whether to start RViz'
        ),
        # 使用OpaqueFunction处理动态逻辑
        OpaqueFunction(function=launch_setup)
    ])