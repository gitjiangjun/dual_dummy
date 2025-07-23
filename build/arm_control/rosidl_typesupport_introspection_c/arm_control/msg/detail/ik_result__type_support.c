// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from arm_control:msg/IKResult.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "arm_control/msg/detail/ik_result__rosidl_typesupport_introspection_c.h"
#include "arm_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "arm_control/msg/detail/ik_result__functions.h"
#include "arm_control/msg/detail/ik_result__struct.h"


// Include directives for member types
// Member `arm_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `joint_angles`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  arm_control__msg__IKResult__init(message_memory);
}

void arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_fini_function(void * message_memory)
{
  arm_control__msg__IKResult__fini(message_memory);
}

size_t arm_control__msg__IKResult__rosidl_typesupport_introspection_c__size_function__IKResult__joint_angles(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_const_function__IKResult__joint_angles(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_function__IKResult__joint_angles(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void arm_control__msg__IKResult__rosidl_typesupport_introspection_c__fetch_function__IKResult__joint_angles(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_const_function__IKResult__joint_angles(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void arm_control__msg__IKResult__rosidl_typesupport_introspection_c__assign_function__IKResult__joint_angles(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_function__IKResult__joint_angles(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool arm_control__msg__IKResult__rosidl_typesupport_introspection_c__resize_function__IKResult__joint_angles(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_member_array[3] = {
  {
    "arm_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_control__msg__IKResult, arm_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "joint_angles",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_control__msg__IKResult, joint_angles),  // bytes offset in struct
    NULL,  // default value
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__size_function__IKResult__joint_angles,  // size() function pointer
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_const_function__IKResult__joint_angles,  // get_const(index) function pointer
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__get_function__IKResult__joint_angles,  // get(index) function pointer
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__fetch_function__IKResult__joint_angles,  // fetch(index, &value) function pointer
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__assign_function__IKResult__joint_angles,  // assign(index, value) function pointer
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__resize_function__IKResult__joint_angles  // resize(index) function pointer
  },
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_control__msg__IKResult, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_members = {
  "arm_control__msg",  // message namespace
  "IKResult",  // message name
  3,  // number of fields
  sizeof(arm_control__msg__IKResult),
  arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_member_array,  // message members
  arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_init_function,  // function to initialize message memory (memory has to be allocated)
  arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_type_support_handle = {
  0,
  &arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_arm_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_control, msg, IKResult)() {
  if (!arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_type_support_handle.typesupport_identifier) {
    arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &arm_control__msg__IKResult__rosidl_typesupport_introspection_c__IKResult_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
