// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rboot_interface:msg/ObjectPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__TRAITS_HPP_
#define RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rboot_interface/msg/detail/object_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rboot_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const ObjectPosition & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectPosition & msg, bool use_flow_style = false)
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
  const rboot_interface::msg::ObjectPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  rboot_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rboot_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const rboot_interface::msg::ObjectPosition & msg)
{
  return rboot_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rboot_interface::msg::ObjectPosition>()
{
  return "rboot_interface::msg::ObjectPosition";
}

template<>
inline const char * name<rboot_interface::msg::ObjectPosition>()
{
  return "rboot_interface/msg/ObjectPosition";
}

template<>
struct has_fixed_size<rboot_interface::msg::ObjectPosition>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rboot_interface::msg::ObjectPosition>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rboot_interface::msg::ObjectPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RBOOT_INTERFACE__MSG__DETAIL__OBJECT_POSITION__TRAITS_HPP_
