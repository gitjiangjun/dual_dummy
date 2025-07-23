// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from arm_control:msg/ControlCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__TRAITS_HPP_
#define ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "arm_control/msg/detail/control_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace arm_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const ControlCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: arm_name
  {
    out << "arm_name: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_name, out);
    out << ", ";
  }

  // member: command_type
  {
    out << "command_type: ";
    rosidl_generator_traits::value_to_yaml(msg.command_type, out);
    out << ", ";
  }

  // member: gripper_state
  {
    out << "gripper_state: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ControlCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: arm_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arm_name: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_name, out);
    out << "\n";
  }

  // member: command_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command_type: ";
    rosidl_generator_traits::value_to_yaml(msg.command_type, out);
    out << "\n";
  }

  // member: gripper_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gripper_state: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ControlCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace arm_control

namespace rosidl_generator_traits
{

[[deprecated("use arm_control::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_control::msg::ControlCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const arm_control::msg::ControlCommand & msg)
{
  return arm_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<arm_control::msg::ControlCommand>()
{
  return "arm_control::msg::ControlCommand";
}

template<>
inline const char * name<arm_control::msg::ControlCommand>()
{
  return "arm_control/msg/ControlCommand";
}

template<>
struct has_fixed_size<arm_control::msg::ControlCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<arm_control::msg::ControlCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<arm_control::msg::ControlCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__TRAITS_HPP_
