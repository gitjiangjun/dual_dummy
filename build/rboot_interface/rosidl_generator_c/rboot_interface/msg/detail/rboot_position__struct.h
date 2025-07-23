// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice

#ifndef RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_H_
#define RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/RbootPosition in the package rboot_interface.
typedef struct rboot_interface__msg__RbootPosition
{
  int32_t nodeid;
  float position;
  float velocity;
  float torque;
} rboot_interface__msg__RbootPosition;

// Struct for a sequence of rboot_interface__msg__RbootPosition.
typedef struct rboot_interface__msg__RbootPosition__Sequence
{
  rboot_interface__msg__RbootPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rboot_interface__msg__RbootPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RBOOT_INTERFACE__MSG__DETAIL__RBOOT_POSITION__STRUCT_H_
