cmake_minimum_required(VERSION 3.8)
project(arm_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 寻找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)
find_package(kdl_parser REQUIRED)

# 自定义消息生成
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/IKResult.msg"
  "msg/TrajectoryPoint.msg"
  "msg/ControlCommand.msg"
  DEPENDENCIES builtin_interfaces sensor_msgs visualization_msgs
)

#获取类型支持目标,关系到自定义消息
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp
)

# 编译motionlib静态库（核心运动学算法）
add_library(motionlib STATIC
  src/motionlib.cpp
)
target_include_directories(motionlib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>  # 包含motionlib.h所在目录
  $<INSTALL_INTERFACE:src>
  ${EIGEN3_INCLUDE_DIRS}
)
ament_target_dependencies(motionlib
  rclcpp
  Eigen3
)

# 1. IK节点
add_executable(ik_node src/ik_node.cpp)
ament_target_dependencies(ik_node
  rclcpp
  sensor_msgs
  Eigen3
  urdf
  kdl_parser
)
# 链接自定义消息和motionlib库
target_link_libraries(ik_node
  ${cpp_typesupport_target}
  Eigen3::Eigen
  motionlib  # 链接运动学库
  ${urdf_LIBRARIES}
  ${kdl_parser_LIBRARIES}
)

# 2. 轨迹规划节点
add_executable(trajectory_node src/trajectory_node.cpp)
ament_target_dependencies(trajectory_node
  rclcpp
  sensor_msgs
  Eigen3
)
target_link_libraries(trajectory_node
  ${cpp_typesupport_target}
  Eigen3::Eigen
  motionlib  # 链接运动学库
)

# 3. 控制器节点
add_executable(arm_controller_node src/controller_node.cpp)
ament_target_dependencies(arm_controller_node
  rclcpp
  sensor_msgs
  Eigen3
)
target_link_libraries(arm_controller_node
  ${cpp_typesupport_target}
  Eigen3::Eigen
  motionlib  # 链接运动学库
)

# 4. 轨迹可视化节点
add_executable(trajectory_viewer src/trajectory_viewer.cpp)
ament_target_dependencies(trajectory_viewer
  rclcpp
  sensor_msgs
  visualization_msgs
  Eigen3
  urdf
  kdl_parser
)
target_link_libraries(trajectory_viewer
  ${cpp_typesupport_target}
  Eigen3::Eigen
  motionlib  # 链接运动学库
)

# 安装可执行文件
install(TARGETS
  ik_node
  trajectory_node
  arm_controller_node
  trajectory_viewer
  DESTINATION lib/${PROJECT_NAME}
)

# 安装消息和配置文件
install(DIRECTORY
  msg
  DESTINATION share/${PROJECT_NAME}
)

# 安装launch文件
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# 测试相关配置
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()