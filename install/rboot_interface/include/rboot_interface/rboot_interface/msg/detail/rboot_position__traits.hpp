// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__TRAITS_HPP_
#define RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rboot_interface/msg/detail/rboot_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rboot_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const RbootPosition & msg,
  std::ostream & out)
{
  out << "{";
  // member: nodeid
  {
    out << "nodeid: ";
    rosidl_generator_traits::value_to_yaml(msg.nodeid, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: torque
  {
    out << "torque: ";
    rosidl_generator_traits::value_to_yaml(msg.torque, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RbootPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: nodeid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nodeid: ";
    rosidl_generator_traits::value_to_yaml(msg.nodeid, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << "\n";
  }

  // member: torque
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torque: ";
    rosidl_generator_traits::value_to_yaml(msg.torque, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RbootPosition & msg, bool use_flow_style = false)
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

}  // namespace rboot_interface

namespace rosidl_generator_traits
{

[[deprecated("use rboot_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rboot_interface::msg::RbootPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  rboot_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rboot_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const rboot_interface::msg::RbootPosition & msg)
{
  return rboot_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rboot_interface::msg::RbootPosition>()
{
  return "rboot_interface::msg::RbootPosition";
}

template<>
inline const char * name<rboot_interface::msg::RbootPosition>()
{
  return "rboot_interface/msg/RbootPosition";
}

template<>
struct has_fixed_size<rboot_interface::msg::RbootPosition>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rboot_interface::msg::RbootPosition>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rboot_interface::msg::RbootPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__TRAITS_HPP_
