// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/IKResult.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__IK_RESULT__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__IK_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/ik_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_IKResult_success
{
public:
  explicit Init_IKResult_success(::arm_control::msg::IKResult & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::IKResult success(::arm_control::msg::IKResult::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::IKResult msg_;
};

class Init_IKResult_joint_angles
{
public:
  explicit Init_IKResult_joint_angles(::arm_control::msg::IKResult & msg)
  : msg_(msg)
  {}
  Init_IKResult_success joint_angles(::arm_control::msg::IKResult::_joint_angles_type arg)
  {
    msg_.joint_angles = std::move(arg);
    return Init_IKResult_success(msg_);
  }

private:
  ::arm_control::msg::IKResult msg_;
};

class Init_IKResult_arm_name
{
public:
  Init_IKResult_arm_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IKResult_joint_angles arm_name(::arm_control::msg::IKResult::_arm_name_type arg)
  {
    msg_.arm_name = std::move(arg);
    return Init_IKResult_joint_angles(msg_);
  }

private:
  ::arm_control::msg::IKResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::IKResult>()
{
  return arm_control::msg::builder::Init_IKResult_arm_name();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__IK_RESULT__BUILDER_HPP_
