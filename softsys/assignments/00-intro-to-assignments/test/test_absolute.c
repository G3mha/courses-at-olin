#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/absolute.h"

// Check that zero has an absolute value of zero.
Test(absolute_value, absolute_zero) {
  cr_assert(eq(int, absolute_value(0), 0));
}

// Check that a positive number is the same as its absolute value.
Test(absolute_value, absolute_positive) {
  const int positive_int = 42;
  cr_assert(eq(int, absolute_value(positive_int), positive_int));
}

// Check that a negative number is the negative of its absolute value.
Test(absolute_value, absolute_negative) {
  const int negative_int = -42;
  cr_assert(eq(int, absolute_value(negative_int), -negative_int));
}
