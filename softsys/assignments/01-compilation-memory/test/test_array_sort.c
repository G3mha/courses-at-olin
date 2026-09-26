#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/array_sort.h"

// Swapping the same memory location should keep that value in place.
Test(swap, swap_same_location) {
  int num = 0;
  swap(&num, &num);
  cr_assert(eq(int, num, 0));
}

// Swapping two of the same value (at different addresses) should not change
// either value.
Test(swap, swap_same_value) {
  int left_int = 0;
  int right_int = 0;
  swap(&left_int, &right_int);
  cr_assert(eq(int, left_int, 0));
  cr_assert(eq(int, right_int, 0));
}

// Swapping two unequal values should change each value as expected.
Test(swap, swap_unequal) {
  const int LEFT_ORIG = 42;
  const int RIGHT_ORIG = 47;
  int left_int = LEFT_ORIG;
  int right_int = RIGHT_ORIG;
  swap(&left_int, &right_int);
  cr_assert(eq(int, left_int, RIGHT_ORIG));
  cr_assert(eq(int, right_int, LEFT_ORIG));
}

// Sorting an array of a single value in place should leave the array as is.
Test(sort_inplace, singleton_array_unchanged) {
  int singleton[] = {0};
  sort_inplace(singleton, 1);
  cr_assert(eq(int, singleton[0], 0));
}

// Sorting an array in order should leave the array as is.
Test(sort_inplace, sorted_array_unchanged) {
  int sorted[] = {0, 1, 2};
  sort_inplace(sorted, 3);
  cr_assert(eq(int, sorted[0], 0));
  cr_assert(eq(int, sorted[1], 1));
  cr_assert(eq(int, sorted[2], 2));
}

// Sorting an array not already in order should change its order.
Test(sort_inplace, unsorted_array_changed) {
  int unsorted[] = {1, 0, 2};
  sort_inplace(unsorted, 3);
  cr_assert(eq(int, unsorted[0], 0));
  cr_assert(eq(int, unsorted[1], 1));
  cr_assert(eq(int, unsorted[2], 2));
}

// Sorting should be able to handle negative integers.
Test(sort_inplace, sort_negative_values) {
  int unsorted[] = {0, -1, 1};
  sort_inplace(unsorted, 3);
  cr_assert(eq(int, unsorted[0], -1));
  cr_assert(eq(int, unsorted[1], 0));
  cr_assert(eq(int, unsorted[2], 1));
}

// Sorting into a copy should not change the original array.
Test(sort_copy, original_array_unchanged) {
  int unsorted[] = {1, 0, 2};
  int sorted[3];
  sort_copy(unsorted, sorted, 3);
  cr_assert(eq(int, unsorted[0], 1));
  cr_assert(eq(int, unsorted[1], 0));
  cr_assert(eq(int, unsorted[2], 2));
}

// Sorting into a copy should result in a sorted copy.
Test(sort_copy, sorted_array_in_order) {
  int unsorted[] = {1, 0, 2};
  int sorted[3];
  sort_copy(unsorted, sorted, 3);
  cr_assert(eq(int, sorted[0], 0));
  cr_assert(eq(int, sorted[1], 1));
  cr_assert(eq(int, sorted[2], 2));
}
