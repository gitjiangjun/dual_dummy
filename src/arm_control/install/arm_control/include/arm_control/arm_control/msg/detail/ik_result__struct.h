// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/IKResult.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'arm_name'
#include "rosidl_runtime_c/string.h"
// Member 'joint_angles'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/IKResult in the package arm_control.
typedef struct arm_control__msg__IKResult
{
  /// left_arm / right_arm
  rosidl_runtime_c__String arm_name;
  /// 7个关节角
  rosidl_runtime_c__double__Sequence joint_angles;
  /// 求解是否成功
  bool success;
} arm_control__msg__IKResult;

// Struct for a sequence of arm_control__msg__IKResult.
typedef struct arm_control__msg__IKResult__Sequence
{
  arm_control__msg__IKResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__IKResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__IK_RESULT__STRUCT_H_
