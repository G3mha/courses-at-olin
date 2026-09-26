#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdlib.h>

#include "../src/string_array.h"

// NOLINTBEGIN(*-magic-numbers)

// Check that a new array has size 0.
Test(make_string_array, created_with_zero_size) {
  string_array* array = make_string_array(1);
  cr_expect(zero(sz, array->size));
  free_string_array(array);
}

// Check that a new array has the given capacity (zero).
Test(make_string_array, create_with_zero_capacity) {
  string_array* array = make_string_array(0);
  cr_expect(zero(sz, array->capacity));
  free_string_array(array);
}

// Check that a new array has the given capacity (nonzero).
Test(make_string_array, create_with_nonzero_capacity) {
  string_array* array = make_string_array(1);
  cr_expect(eq(sz, array->capacity, 1));
  free_string_array(array);
}

// Check that a new array has NULL as its first pointer (zero capacity).
Test(make_string_array, sentinel_pointer_zero_capacity) {
  string_array* array = make_string_array(0);
  cr_expect(zero(ptr, array->strings[0]));
  free_string_array(array);
}

// Check that a new array has NULL as its first pointer (nonzero capacity).
Test(make_string_array, sentinel_pointer_nonzero_capacity) {
  string_array* array = make_string_array(1);
  cr_expect(zero(ptr, array->strings[0]));
  free_string_array(array);
}

// No tests for free_string_array.

// Check that resizing an array to a larger capacity does not change its size.
Test(resize, grow_preserves_size) {
  string_array* array = make_string_array(1);
  cr_expect(zero(sz, array->size));
  free_string_array(array);
}

// Check that resizing an array to a larger capacity has that new capacity.
Test(resize, grow_increases_capacity) {
  string_array* array = make_string_array(0);
  resize(array, 1);
  cr_expect(eq(sz, array->capacity, 1));
  free_string_array(array);
}

// Check that resizing an array to a smaller capacity has that new capacity.
Test(resize, shrink_decreases_capacity) {
  string_array* array = make_string_array(1);
  resize(array, 0);
  cr_expect(zero(sz, array->capacity));
  free_string_array(array);
}

// Check that resizing an array to a smaller capacity shrinks the size.
Test(resize, shrink_decreases_size) {
  string_array* array = make_string_array(1);
  add_string(array, "Hello", 5);
  resize(array, 0);
  cr_expect(zero(sz, array->size));
  free_string_array(array);
}

// Check that resizing an array to a smaller capacity sets the null pointer
// appropriately.
Test(resize, shrink_moves_sentinel_pointer) {
  string_array* array = make_string_array(1);
  add_string(array, "Hello", 5);
  resize(array, 0);
  cr_expect(zero(ptr, array->strings[0]));
  free_string_array(array);
}

// Check that adding a string to an array increases its size by 1.
Test(add_string, add_increases_size) {
  string_array* array = make_string_array(1);
  add_string(array, "Hello", 5);
  cr_expect(eq(sz, array->size, 1));
  free_string_array(array);
}

// Check that adding a string to an array moves the terminating null pointer.
Test(add_string, add_moves_sentinel_pointer) {
  string_array* array = make_string_array(1);
  add_string(array, "Hello", 5);
  cr_expect(zero(ptr, array->strings[1]));
  free_string_array(array);
}

// Check that adding a string to a zero-capacity array increases its capacity
// to 1.
Test(add_string, add_increments_zero_capacity) {
  string_array* array = make_string_array(0);
  add_string(array, "Hello", 5);
  cr_expect(eq(sz, array->capacity, 1));
  free_string_array(array);
}

// Check that adding a string to a nonzero-capacity array when it is full
// doubles its capacity.
Test(add_string, add_doubles_nonzero_capacity) {
  string_array* array = make_string_array(1);
  add_string(array, "Hello", 5);
  add_string(array, "Hello", 5);
  cr_expect(eq(sz, array->capacity, 2));
  free_string_array(array);
}

// NOLINTEND(*-magic-numbers)
