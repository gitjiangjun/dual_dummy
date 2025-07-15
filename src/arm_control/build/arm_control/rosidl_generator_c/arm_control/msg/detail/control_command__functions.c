// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from arm_control:msg/ControlCommand.idl
// generated code does not contain a copyright notice
#include "arm_control/msg/detail/control_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `arm_name`
// Member `command_type`
// Member `gripper_state`
#include "rosidl_runtime_c/string_functions.h"

bool
arm_control__msg__ControlCommand__init(arm_control__msg__ControlCommand * msg)
{
  if (!msg) {
    return false;
  }
  // arm_name
  if (!rosidl_runtime_c__String__init(&msg->arm_name)) {
    arm_control__msg__ControlCommand__fini(msg);
    return false;
  }
  // command_type
  if (!rosidl_runtime_c__String__init(&msg->command_type)) {
    arm_control__msg__ControlCommand__fini(msg);
    return false;
  }
  // gripper_state
  if (!rosidl_runtime_c__String__init(&msg->gripper_state)) {
    arm_control__msg__ControlCommand__fini(msg);
    return false;
  }
  return true;
}

void
arm_control__msg__ControlCommand__fini(arm_control__msg__ControlCommand * msg)
{
  if (!msg) {
    return;
  }
  // arm_name
  rosidl_runtime_c__String__fini(&msg->arm_name);
  // command_type
  rosidl_runtime_c__String__fini(&msg->command_type);
  // gripper_state
  rosidl_runtime_c__String__fini(&msg->gripper_state);
}

bool
arm_control__msg__ControlCommand__are_equal(const arm_control__msg__ControlCommand * lhs, const arm_control__msg__ControlCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // arm_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->arm_name), &(rhs->arm_name)))
  {
    return false;
  }
  // command_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->command_type), &(rhs->command_type)))
  {
    return false;
  }
  // gripper_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->gripper_state), &(rhs->gripper_state)))
  {
    return false;
  }
  return true;
}

bool
arm_control__msg__ControlCommand__copy(
  const arm_control__msg__ControlCommand * input,
  arm_control__msg__ControlCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // arm_name
  if (!rosidl_runtime_c__String__copy(
      &(input->arm_name), &(output->arm_name)))
  {
    return false;
  }
  // command_type
  if (!rosidl_runtime_c__String__copy(
      &(input->command_type), &(output->command_type)))
  {
    return false;
  }
  // gripper_state
  if (!rosidl_runtime_c__String__copy(
      &(input->gripper_state), &(output->gripper_state)))
  {
    return false;
  }
  return true;
}

arm_control__msg__ControlCommand *
arm_control__msg__ControlCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__ControlCommand * msg = (arm_control__msg__ControlCommand *)allocator.allocate(sizeof(arm_control__msg__ControlCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_control__msg__ControlCommand));
  bool success = arm_control__msg__ControlCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_control__msg__ControlCommand__destroy(arm_control__msg__ControlCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_control__msg__ControlCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_control__msg__ControlCommand__Sequence__init(arm_control__msg__ControlCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__ControlCommand * data = NULL;

  if (size) {
    data = (arm_control__msg__ControlCommand *)allocator.zero_allocate(size, sizeof(arm_control__msg__ControlCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_control__msg__ControlCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_control__msg__ControlCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm_control__msg__ControlCommand__Sequence__fini(arm_control__msg__ControlCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm_control__msg__ControlCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm_control__msg__ControlCommand__Sequence *
arm_control__msg__ControlCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__ControlCommand__Sequence * array = (arm_control__msg__ControlCommand__Sequence *)allocator.allocate(sizeof(arm_control__msg__ControlCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_control__msg__ControlCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_control__msg__ControlCommand__Sequence__destroy(arm_control__msg__ControlCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_control__msg__ControlCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_control__msg__ControlCommand__Sequence__are_equal(const arm_control__msg__ControlCommand__Sequence * lhs, const arm_control__msg__ControlCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_control__msg__ControlCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_control__msg__ControlCommand__Sequence__copy(
  const arm_control__msg__ControlCommand__Sequence * input,
  arm_control__msg__ControlCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_control__msg__ControlCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_control__msg__ControlCommand * data =
      (arm_control__msg__ControlCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_control__msg__ControlCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_control__msg__ControlCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_control__msg__ControlCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
