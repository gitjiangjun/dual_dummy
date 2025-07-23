// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rboot_interface/msg/detail/rboot_position__rosidl_typesupport_introspection_c.h"
#include "rboot_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rboot_interface/msg/detail/rboot_position__functions.h"
#include "rboot_interface/msg/detail/rboot_position__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rboot_interface__msg__RbootPosition__init(message_memory);
}

void rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_fini_function(void * message_memory)
{
  rboot_interface__msg__RbootPosition__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_member_array[4] = {
  {
    "nodeid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rboot_interface__msg__RbootPosition, nodeid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rboot_interface__msg__RbootPosition, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rboot_interface__msg__RbootPosition, velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torque",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rboot_interface__msg__RbootPosition, torque),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_members = {
  "rboot_interface__msg",  // message namespace
  "RbootPosition",  // message name
  4,  // number of fields
  sizeof(rboot_interface__msg__RbootPosition),
  rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_member_array,  // message members
  rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_init_function,  // function to initialize message memory (memory has to be allocated)
  rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_type_support_handle = {
  0,
  &rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rboot_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rboot_interface, msg, RbootPosition)() {
  if (!rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_type_support_handle.typesupport_identifier) {
    rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rboot_interface__msg__RbootPosition__rosidl_typesupport_introspection_c__RbootPosition_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
