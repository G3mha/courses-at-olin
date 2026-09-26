#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/string_utils.h"

// An empty string starts with itself.
Test(startswith, empty_identical_strings) {
  const char* str = "";
  const char* substr = "";
  cr_assert(eq(int, startswith(str, substr), 1));
}

// A nonempty string starts with itself.
Test(startswith, nonempty_identical_strings) {
  const char* str = "abc";
  const char* substr = "abc";
  cr_assert(eq(int, startswith(str, substr), 1));
}

// A string always starts with an empty substring.
Test(startswith, empty_substr) {
  const char* str = "abc";
  const char* substr = "";
  cr_assert(eq(int, startswith(str, substr), 1));
}

// A string cannot start with a substring longer than itself.
Test(startswith, longer_substr) {
  const char* str = "abc";
  const char* substr = "abcd";
  cr_assert(zero(int, startswith(str, substr)));
}

// An empty string cannot start with a nonempty substring.
Test(startswith, nonempty_not_in_empty) {
  const char* str = "";
  const char* substr = "a";
  cr_assert(zero(int, startswith(str, substr)));
}

// A string does not start with a substring that has no common characters with
// it.
Test(startswith, no_common_characters) {
  const char* str = "abc";
  const char* substr = "d";
  cr_assert(zero(int, startswith(str, substr)));
}

// A string does not start with a substring that matches it up to a point.
Test(startswith, partial_substr_match) {
  const char* str = "abc";
  const char* substr = "abd";
  cr_assert(zero(int, startswith(str, substr)));
}
