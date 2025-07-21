// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from arm_control:msg/ControlCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_HPP_
#define ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__arm_control__msg__ControlCommand __attribute__((deprecated))
#else
# define DEPRECATED__arm_control__msg__ControlCommand __declspec(deprecated)
#endif

namespace arm_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControlCommand_
{
  using Type = ControlCommand_<ContainerAllocator>;

  explicit ControlCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arm_name = "";
      this->command_type = "";
      this->gripper_state = "";
    }
  }

  explicit ControlCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : arm_name(_alloc),
    command_type(_alloc),
    gripper_state(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arm_name = "";
      this->command_type = "";
      this->gripper_state = "";
    }
  }

  // field types and members
  using _arm_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arm_name_type arm_name;
  using _command_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _command_type_type command_type;
  using _gripper_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _gripper_state_type gripper_state;

  // setters for named parameter idiom
  Type & set__arm_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arm_name = _arg;
    return *this;
  }
  Type & set__command_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->command_type = _arg;
    return *this;
  }
  Type & set__gripper_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->gripper_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    arm_control::msg::ControlCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const arm_control::msg::ControlCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<arm_control::msg::ControlCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<arm_control::msg::ControlCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::ControlCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::ControlCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::ControlCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::ControlCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<arm_control::msg::ControlCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<arm_control::msg::ControlCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__arm_control__msg__ControlCommand
    std::shared_ptr<arm_control::msg::ControlCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__arm_control__msg__ControlCommand
    std::shared_ptr<arm_control::msg::ControlCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlCommand_ & other) const
  {
    if (this->arm_name != other.arm_name) {
      return false;
    }
    if (this->command_type != other.command_type) {
      return false;
    }
    if (this->gripper_state != other.gripper_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlCommand_

// alias to use template instance with default allocator
using ControlCommand =
  arm_control::msg::ControlCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_HPP_
