#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/string_utils.h"

Test(count, empty_string_contains_no_substrings) {
  const char* empty_string = "";
  const char* substr = "a";
  cr_assert(zero(int, count(empty_string, substr)));
}

Test(count, empty_substring) {
  const char* string = "abc";
  const char* empty_substr = "";
  cr_assert(eq(int, (int)strlen(string) + 1, count(string, empty_substr)));
}

Test(count, single_occurrence) {
  const char* string = "abc";
  const char* substr = "a";
  cr_assert(eq(int, count(string, substr), 1));
}

Test(count, multiple_occurrences) {
  const char* string = "canada";
  const char* substr = "a";
  cr_assert(eq(int, count(string, substr), 3));
}

Test(count, overlapping_occurrences) {
  const char* string = "aaaa";
  const char* substr = "aa";
  cr_assert(eq(int, count(string, substr), 2));
}

Test(count, substr_too_long) {
  const char* string = "abc";
  const char* substr = "abcd";
  cr_assert(zero(int, count(string, substr)));
}

Test(count, substr_not_in) {
  const char* string = "abc";
  const char* substr = "d";
  cr_assert(zero(int, count(string, substr)));
}

Test(count, multiple_multichar_substr) {
  const char* string = "banana";
  const char* substr = "an";
  cr_assert(eq(int, count(string, substr), 2));
}
