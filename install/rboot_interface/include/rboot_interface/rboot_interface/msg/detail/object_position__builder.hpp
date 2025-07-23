// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rboot_interface:msg/ObjectPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__BUILDER_HPP_
#define RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rboot_interface/msg/detail/object_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rboot_interface
{

namespace msg
{

namespace builder
{

class Init_ObjectPosition_y
{
public:
  explicit Init_ObjectPosition_y(::rboot_interface::msg::ObjectPosition & msg)
  : msg_(msg)
  {}
  ::rboot_interface::msg::ObjectPosition y(::rboot_interface::msg::ObjectPosition::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rboot_interface::msg::ObjectPosition msg_;
};

class Init_ObjectPosition_x
{
public:
  Init_ObjectPosition_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectPosition_y x(::rboot_interface::msg::ObjectPosition::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ObjectPosition_y(msg_);
  }

private:
  ::rboot_interface::msg::ObjectPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rboot_interface::msg::ObjectPosition>()
{
  return rboot_interface::msg::builder::Init_ObjectPosition_x();
}

}  // namespace rboot_interface

#endif  // RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__BUILDER_HPP_
