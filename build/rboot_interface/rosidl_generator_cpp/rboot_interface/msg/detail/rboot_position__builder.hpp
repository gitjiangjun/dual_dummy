// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__BUILDER_HPP_
#define RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rboot_interface/msg/detail/rboot_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rboot_interface
{

namespace msg
{

namespace builder
{

class Init_RbootPosition_torque
{
public:
  explicit Init_RbootPosition_torque(::rboot_interface::msg::RbootPosition & msg)
  : msg_(msg)
  {}
  ::rboot_interface::msg::RbootPosition torque(::rboot_interface::msg::RbootPosition::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rboot_interface::msg::RbootPosition msg_;
};

class Init_RbootPosition_velocity
{
public:
  explicit Init_RbootPosition_velocity(::rboot_interface::msg::RbootPosition & msg)
  : msg_(msg)
  {}
  Init_RbootPosition_torque velocity(::rboot_interface::msg::RbootPosition::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_RbootPosition_torque(msg_);
  }

private:
  ::rboot_interface::msg::RbootPosition msg_;
};

class Init_RbootPosition_position
{
public:
  explicit Init_RbootPosition_position(::rboot_interface::msg::RbootPosition & msg)
  : msg_(msg)
  {}
  Init_RbootPosition_velocity position(::rboot_interface::msg::RbootPosition::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_RbootPosition_velocity(msg_);
  }

private:
  ::rboot_interface::msg::RbootPosition msg_;
};

class Init_RbootPosition_nodeid
{
public:
  Init_RbootPosition_nodeid()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RbootPosition_position nodeid(::rboot_interface::msg::RbootPosition::_nodeid_type arg)
  {
    msg_.nodeid = std::move(arg);
    return Init_RbootPosition_position(msg_);
  }

private:
  ::rboot_interface::msg::RbootPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rboot_interface::msg::RbootPosition>()
{
  return rboot_interface::msg::builder::Init_RbootPosition_nodeid();
}

}  // namespace rboot_interface

#endif  // RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__BUILDER_HPP_
