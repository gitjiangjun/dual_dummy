// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from arm_control:msg/IKResult.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__IK_RESULT__FUNCTIONS_H_
#define ARM_CONTROL__MSG__DETAIL__IK_RESULT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "arm_control/msg/rosidl_generator_c__visibility_control.h"

#include "arm_control/msg/detail/ik_result__struct.h"

/// Initialize msg/IKResult message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_control__msg__IKResult
 * )) before or use
 * arm_control__msg__IKResult__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__init(arm_control__msg__IKResult * msg);

/// Finalize msg/IKResult message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
void
arm_control__msg__IKResult__fini(arm_control__msg__IKResult * msg);

/// Create msg/IKResult message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_control__msg__IKResult__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
arm_control__msg__IKResult *
arm_control__msg__IKResult__create();

/// Destroy msg/IKResult message.
/**
 * It calls
 * arm_control__msg__IKResult__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
void
arm_control__msg__IKResult__destroy(arm_control__msg__IKResult * msg);

/// Check for msg/IKResult message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__are_equal(const arm_control__msg__IKResult * lhs, const arm_control__msg__IKResult * rhs);

/// Copy a msg/IKResult message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__copy(
  const arm_control__msg__IKResult * input,
  arm_control__msg__IKResult * output);

/// Initialize array of msg/IKResult messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_control__msg__IKResult__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__Sequence__init(arm_control__msg__IKResult__Sequence * array, size_t size);

/// Finalize array of msg/IKResult messages.
/**
 * It calls
 * arm_control__msg__IKResult__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
void
arm_control__msg__IKResult__Sequence__fini(arm_control__msg__IKResult__Sequence * array);

/// Create array of msg/IKResult messages.
/**
 * It allocates the memory for the array and calls
 * arm_control__msg__IKResult__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
arm_control__msg__IKResult__Sequence *
arm_control__msg__IKResult__Sequence__create(size_t size);

/// Destroy array of msg/IKResult messages.
/**
 * It calls
 * arm_control__msg__IKResult__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
void
arm_control__msg__IKResult__Sequence__destroy(arm_control__msg__IKResult__Sequence * array);

/// Check for msg/IKResult message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__Sequence__are_equal(const arm_control__msg__IKResult__Sequence * lhs, const arm_control__msg__IKResult__Sequence * rhs);

/// Copy an array of msg/IKResult messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_control
bool
arm_control__msg__IKResult__Sequence__copy(
  const arm_control__msg__IKResult__Sequence * input,
  arm_control__msg__IKResult__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__IK_RESULT__FUNCTIONS_H_
