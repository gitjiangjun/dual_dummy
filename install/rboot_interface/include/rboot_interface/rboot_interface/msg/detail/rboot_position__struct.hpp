// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_HPP_
#define RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rboot_interface__msg__RbootPosition __attribute__((deprecated))
#else
# define DEPRECATED__rboot_interface__msg__RbootPosition __declspec(deprecated)
#endif

namespace rboot_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RbootPosition_
{
  using Type = RbootPosition_<ContainerAllocator>;

  explicit RbootPosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->nodeid = 0l;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
    }
  }

  explicit RbootPosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->nodeid = 0l;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
    }
  }

  // field types and members
  using _nodeid_type =
    int32_t;
  _nodeid_type nodeid;
  using _position_type =
    float;
  _position_type position;
  using _velocity_type =
    float;
  _velocity_type velocity;
  using _torque_type =
    float;
  _torque_type torque;

  // setters for named parameter idiom
  Type & set__nodeid(
    const int32_t & _arg)
  {
    this->nodeid = _arg;
    return *this;
  }
  Type & set__position(
    const float & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const float & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__torque(
    const float & _arg)
  {
    this->torque = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rboot_interface::msg::RbootPosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const rboot_interface::msg::RbootPosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rboot_interface::msg::RbootPosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rboot_interface::msg::RbootPosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rboot_interface__msg__RbootPosition
    std::shared_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rboot_interface__msg__RbootPosition
    std::shared_ptr<rboot_interface::msg::RbootPosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RbootPosition_ & other) const
  {
    if (this->nodeid != other.nodeid) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    return true;
  }
  bool operator!=(const RbootPosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RbootPosition_

// alias to use template instance with default allocator
using RbootPosition =
  rboot_interface::msg::RbootPosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rboot_interface

#endif  // RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_HPP_
