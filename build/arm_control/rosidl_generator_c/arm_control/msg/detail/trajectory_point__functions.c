// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from arm_control:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice
#include "arm_control/msg/detail/trajectory_point__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `arm_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `positions`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
arm_control__msg__TrajectoryPoint__init(arm_control__msg__TrajectoryPoint * msg)
{
  if (!msg) {
    return false;
  }
  // arm_name
  if (!rosidl_runtime_c__String__init(&msg->arm_name)) {
    arm_control__msg__TrajectoryPoint__fini(msg);
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__init(&msg->positions, 0)) {
    arm_control__msg__TrajectoryPoint__fini(msg);
    return false;
  }
  // time_from_start
  return true;
}

void
arm_control__msg__TrajectoryPoint__fini(arm_control__msg__TrajectoryPoint * msg)
{
  if (!msg) {
    return;
  }
  // arm_name
  rosidl_runtime_c__String__fini(&msg->arm_name);
  // positions
  rosidl_runtime_c__double__Sequence__fini(&msg->positions);
  // time_from_start
}

bool
arm_control__msg__TrajectoryPoint__are_equal(const arm_control__msg__TrajectoryPoint * lhs, const arm_control__msg__TrajectoryPoint * rhs)
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
  // positions
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->positions), &(rhs->positions)))
  {
    return false;
  }
  // time_from_start
  if (lhs->time_from_start != rhs->time_from_start) {
    return false;
  }
  return true;
}

bool
arm_control__msg__TrajectoryPoint__copy(
  const arm_control__msg__TrajectoryPoint * input,
  arm_control__msg__TrajectoryPoint * output)
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
  // positions
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->positions), &(output->positions)))
  {
    return false;
  }
  // time_from_start
  output->time_from_start = input->time_from_start;
  return true;
}

arm_control__msg__TrajectoryPoint *
arm_control__msg__TrajectoryPoint__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__TrajectoryPoint * msg = (arm_control__msg__TrajectoryPoint *)allocator.allocate(sizeof(arm_control__msg__TrajectoryPoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_control__msg__TrajectoryPoint));
  bool success = arm_control__msg__TrajectoryPoint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_control__msg__TrajectoryPoint__destroy(arm_control__msg__TrajectoryPoint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_control__msg__TrajectoryPoint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_control__msg__TrajectoryPoint__Sequence__init(arm_control__msg__TrajectoryPoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__TrajectoryPoint * data = NULL;

  if (size) {
    data = (arm_control__msg__TrajectoryPoint *)allocator.zero_allocate(size, sizeof(arm_control__msg__TrajectoryPoint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_control__msg__TrajectoryPoint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_control__msg__TrajectoryPoint__fini(&data[i - 1]);
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
arm_control__msg__TrajectoryPoint__Sequence__fini(arm_control__msg__TrajectoryPoint__Sequence * array)
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
      arm_control__msg__TrajectoryPoint__fini(&array->data[i]);
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

arm_control__msg__TrajectoryPoint__Sequence *
arm_control__msg__TrajectoryPoint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_control__msg__TrajectoryPoint__Sequence * array = (arm_control__msg__TrajectoryPoint__Sequence *)allocator.allocate(sizeof(arm_control__msg__TrajectoryPoint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_control__msg__TrajectoryPoint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_control__msg__TrajectoryPoint__Sequence__destroy(arm_control__msg__TrajectoryPoint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_control__msg__TrajectoryPoint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_control__msg__TrajectoryPoint__Sequence__are_equal(const arm_control__msg__TrajectoryPoint__Sequence * lhs, const arm_control__msg__TrajectoryPoint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_control__msg__TrajectoryPoint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_control__msg__TrajectoryPoint__Sequence__copy(
  const arm_control__msg__TrajectoryPoint__Sequence * input,
  arm_control__msg__TrajectoryPoint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_control__msg__TrajectoryPoint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_control__msg__TrajectoryPoint * data =
      (arm_control__msg__TrajectoryPoint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_control__msg__TrajectoryPoint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_control__msg__TrajectoryPoint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_control__msg__TrajectoryPoint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
