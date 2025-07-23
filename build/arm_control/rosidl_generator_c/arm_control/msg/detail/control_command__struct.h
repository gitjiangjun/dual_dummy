// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/ControlCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_H_

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
// Member 'command_type'
// Member 'gripper_state'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ControlCommand in the package arm_control.
typedef struct arm_control__msg__ControlCommand
{
  /// left_arm / right_arm / both_arms
  rosidl_runtime_c__String arm_name;
  /// gripper
  rosidl_runtime_c__String command_type;
  /// open / close
  rosidl_runtime_c__String gripper_state;
} arm_control__msg__ControlCommand;

// Struct for a sequence of arm_control__msg__ControlCommand.
typedef struct arm_control__msg__ControlCommand__Sequence
{
  arm_control__msg__ControlCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__ControlCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__CONTROL_COMMAND__STRUCT_H_
