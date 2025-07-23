// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from arm_control:msg/IKResult.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_HPP_
#define ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__arm_control__msg__IKResult __attribute__((deprecated))
#else
# define DEPRECATED__arm_control__msg__IKResult __declspec(deprecated)
#endif

namespace arm_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IKResult_
{
  using Type = IKResult_<ContainerAllocator>;

  explicit IKResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arm_name = "";
      this->success = false;
    }
  }

  explicit IKResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : arm_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arm_name = "";
      this->success = false;
    }
  }

  // field types and members
  using _arm_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arm_name_type arm_name;
  using _joint_angles_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _joint_angles_type joint_angles;
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__arm_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arm_name = _arg;
    return *this;
  }
  Type & set__joint_angles(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->joint_angles = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    arm_control::msg::IKResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const arm_control::msg::IKResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<arm_control::msg::IKResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<arm_control::msg::IKResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::IKResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::IKResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::IKResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::IKResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<arm_control::msg::IKResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<arm_control::msg::IKResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__arm_control__msg__IKResult
    std::shared_ptr<arm_control::msg::IKResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__arm_control__msg__IKResult
    std::shared_ptr<arm_control::msg::IKResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IKResult_ & other) const
  {
    if (this->arm_name != other.arm_name) {
      return false;
    }
    if (this->joint_angles != other.joint_angles) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const IKResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IKResult_

// alias to use template instance with default allocator
using IKResult =
  arm_control::msg::IKResult_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_HPP_
