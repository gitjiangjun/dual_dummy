// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/ControlCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/control_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_ControlCommand_gripper_state
{
public:
  explicit Init_ControlCommand_gripper_state(::arm_control::msg::ControlCommand & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::ControlCommand gripper_state(::arm_control::msg::ControlCommand::_gripper_state_type arg)
  {
    msg_.gripper_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::ControlCommand msg_;
};

class Init_ControlCommand_command_type
{
public:
  explicit Init_ControlCommand_command_type(::arm_control::msg::ControlCommand & msg)
  : msg_(msg)
  {}
  Init_ControlCommand_gripper_state command_type(::arm_control::msg::ControlCommand::_command_type_type arg)
  {
    msg_.command_type = std::move(arg);
    return Init_ControlCommand_gripper_state(msg_);
  }

private:
  ::arm_control::msg::ControlCommand msg_;
};

class Init_ControlCommand_arm_name
{
public:
  Init_ControlCommand_arm_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlCommand_command_type arm_name(::arm_control::msg::ControlCommand::_arm_name_type arg)
  {
    msg_.arm_name = std::move(arg);
    return Init_ControlCommand_command_type(msg_);
  }

private:
  ::arm_control::msg::ControlCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::ControlCommand>()
{
  return arm_control::msg::builder::Init_ControlCommand_arm_name();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__BUILDER_HPP_
