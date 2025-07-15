// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/trajectory_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_TrajectoryPoint_time_from_start
{
public:
  explicit Init_TrajectoryPoint_time_from_start(::arm_control::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::TrajectoryPoint time_from_start(::arm_control::msg::TrajectoryPoint::_time_from_start_type arg)
  {
    msg_.time_from_start = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_positions
{
public:
  explicit Init_TrajectoryPoint_positions(::arm_control::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  Init_TrajectoryPoint_time_from_start positions(::arm_control::msg::TrajectoryPoint::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return Init_TrajectoryPoint_time_from_start(msg_);
  }

private:
  ::arm_control::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_arm_name
{
public:
  Init_TrajectoryPoint_arm_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrajectoryPoint_positions arm_name(::arm_control::msg::TrajectoryPoint::_arm_name_type arg)
  {
    msg_.arm_name = std::move(arg);
    return Init_TrajectoryPoint_positions(msg_);
  }

private:
  ::arm_control::msg::TrajectoryPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::TrajectoryPoint>()
{
  return arm_control::msg::builder::Init_TrajectoryPoint_arm_name();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_
