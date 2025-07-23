// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rboot_interface:msg/RbootPosition.idl
// generated code does not contain a copyright notice
#include "rboot_interface/msg/detail/rboot_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rboot_interface__msg__RbootPosition__init(rboot_interface__msg__RbootPosition * msg)
{
  if (!msg) {
    return false;
  }
  // nodeid
  // position
  // velocity
  // torque
  return true;
}

void
rboot_interface__msg__RbootPosition__fini(rboot_interface__msg__RbootPosition * msg)
{
  if (!msg) {
    return;
  }
  // nodeid
  // position
  // velocity
  // torque
}

bool
rboot_interface__msg__RbootPosition__are_equal(const rboot_interface__msg__RbootPosition * lhs, const rboot_interface__msg__RbootPosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // nodeid
  if (lhs->nodeid != rhs->nodeid) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  return true;
}

bool
rboot_interface__msg__RbootPosition__copy(
  const rboot_interface__msg__RbootPosition * input,
  rboot_interface__msg__RbootPosition * output)
{
  if (!input || !output) {
    return false;
  }
  // nodeid
  output->nodeid = input->nodeid;
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  // torque
  output->torque = input->torque;
  return true;
}

rboot_interface__msg__RbootPosition *
rboot_interface__msg__RbootPosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rboot_interface__msg__RbootPosition * msg = (rboot_interface__msg__RbootPosition *)allocator.allocate(sizeof(rboot_interface__msg__RbootPosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rboot_interface__msg__RbootPosition));
  bool success = rboot_interface__msg__RbootPosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rboot_interface__msg__RbootPosition__destroy(rboot_interface__msg__RbootPosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rboot_interface__msg__RbootPosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rboot_interface__msg__RbootPosition__Sequence__init(rboot_interface__msg__RbootPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rboot_interface__msg__RbootPosition * data = NULL;

  if (size) {
    data = (rboot_interface__msg__RbootPosition *)allocator.zero_allocate(size, sizeof(rboot_interface__msg__RbootPosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rboot_interface__msg__RbootPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rboot_interface__msg__RbootPosition__fini(&data[i - 1]);
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
rboot_interface__msg__RbootPosition__Sequence__fini(rboot_interface__msg__RbootPosition__Sequence * array)
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
      rboot_interface__msg__RbootPosition__fini(&array->data[i]);
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

rboot_interface__msg__RbootPosition__Sequence *
rboot_interface__msg__RbootPosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rboot_interface__msg__RbootPosition__Sequence * array = (rboot_interface__msg__RbootPosition__Sequence *)allocator.allocate(sizeof(rboot_interface__msg__RbootPosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rboot_interface__msg__RbootPosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rboot_interface__msg__RbootPosition__Sequence__destroy(rboot_interface__msg__RbootPosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rboot_interface__msg__RbootPosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rboot_interface__msg__RbootPosition__Sequence__are_equal(const rboot_interface__msg__RbootPosition__Sequence * lhs, const rboot_interface__msg__RbootPosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rboot_interface__msg__RbootPosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rboot_interface__msg__RbootPosition__Sequence__copy(
  const rboot_interface__msg__RbootPosition__Sequence * input,
  rboot_interface__msg__RbootPosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rboot_interface__msg__RbootPosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rboot_interface__msg__RbootPosition * data =
      (rboot_interface__msg__RbootPosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rboot_interface__msg__RbootPosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rboot_interface__msg__RbootPosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rboot_interface__msg__RbootPosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
