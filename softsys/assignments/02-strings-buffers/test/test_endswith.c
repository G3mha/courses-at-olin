#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/string_utils.h"

// An empty string ends with itself.
Test(endswith, empty_identical_strings) {
  const char* str = "";
  const char* substr = "";
  cr_assert(eq(int, endswith(str, substr), 1));
}

// A nonempty string ends with itself.
Test(endswith, nonempty_identical_strings) {
  const char* str = "abc";
  const char* substr = "abc";
  cr_assert(eq(int, endswith(str, substr), 1));
}

// A string always ends with an empty substring.
Test(endswith, empty_substr) {
  const char* str = "abc";
  const char* substr = "";
  cr_assert(eq(int, endswith(str, substr), 1));
}

// A string cannot end with a substring longer than itself.
Test(endswith, longer_substr) {
  const char* str = "bcd";
  const char* substr = "abcd";
  cr_assert(zero(int, endswith(str, substr)));
}

// An empty string cannot end with a nonempty substring.
Test(endswith, nonempty_not_in_empty) {
  const char* str = "";
  const char* substr = "a";
  cr_assert(zero(int, endswith(str, substr)));
}

// A string does not end with a substring that has no common characters with
// it.
Test(endswith, no_common_characters) {
  const char* str = "abc";
  const char* substr = "d";
  cr_assert(zero(int, endswith(str, substr)));
}

// A string does not end with a substring that matches it up to a point,
// starting from the beginning.
Test(endswith, partial_substr_match_beginning) {
  const char* str = "abc";
  const char* substr = "abd";
  cr_assert(zero(int, endswith(str, substr)));
}

// A string does not end with a substring that matches it up to a point,
// starting from the end
Test(endswith, partial_substr_match_end) {
  const char* str = "abc";
  const char* substr = "dbc";
  cr_assert(zero(int, endswith(str, substr)));
}
