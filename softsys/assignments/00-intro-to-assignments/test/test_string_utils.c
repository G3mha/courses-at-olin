#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/string_utils.h"

// Check that an empty string has length zero.
Test(string_length, empty_string_zero_length) {
  const char* empty_string = "";
  cr_assert(eq(sz, string_length(empty_string), 0));
}

// Check that a nonempty string has any positive length.
Test(string_length, nonempty_string_positive_length) {
  const char* nonempty_string = "Never gonna give you up";
  cr_assert(gt(sz, string_length(nonempty_string), 0));
}

// Check that a nonempty string's length is computed correctly.
Test(string_length, nonempty_string_length_match) {
  const char* nonempty_string = "Never gonna give you up";
  cr_assert(eq(sz, string_length(nonempty_string), strlen(nonempty_string)));
}

// Check that a string with one of its middle characters changed to the sentinel
// character (\0) has its length terminated there.
Test(string_length, nonempty_string_with_early_sentinel) {
  char mutable_string[] = "Never gonna give you up";
  const size_t end_position = 11;
  mutable_string[end_position] = '\0';
  cr_assert(eq(sz, string_length(mutable_string), end_position));
}

// Check that a nonempty string with its first character changed to the sentinel
// character (\0) has its length computed as zero.
Test(string_length, nonempty_string_with_initial_sentinel) {
  char mutable_string[] = "Software Systems";
  mutable_string[0] = '\0';
  cr_assert(eq(sz, string_length(mutable_string), 0));
}

// Check that an empty string has no vowels.
Test(count_vowels, empty_string_no_vowels) {
  const char* empty_string = "";
  cr_assert(eq(sz, count_vowels(empty_string), 0));
}

// Check that a nonempty string with no vowels is reported as having no vowels.
Test(count_vowels, nonempty_string_no_vowels) {
  const char* nonempty_string = "C";
  cr_assert(eq(sz, count_vowels(nonempty_string), 0));
}

// Check that a nonempty string with a vowel has its vowels counted.
Test(count_vowels, nonempty_string_with_vowels) {
  const char* nonempty_string = "e. e. cummings";
  cr_assert(eq(sz, count_vowels(nonempty_string), 4));
}

// Check that both uppercase and lowercase vowels are counted.
Test(count_vowels, vowel_cases_counted) {
  const char* vowels = "AEIOUaeiou";
  cr_assert(eq(sz, count_vowels(vowels), 10));
}

// Check that an empty string has no digits.
Test(count_digits, empty_string_no_digits) {
  const char* empty_string = "";
  cr_assert(eq(sz, count_digits(empty_string), 0));
}

// Check that a non-empty string with no digits is reported as having no digits.
Test(count_digits, nonempty_string_no_digits) {
  const char* nonempty_string = "Never gonna give you up";
  cr_assert(eq(sz, count_digits(nonempty_string), 0));
}

// Check that a non-empty string with digits is counted correctly.
Test(count_digits, nonempty_string_with_digits) {
  const char* nonempty_string = "99 bottles of beer on the wall";
  cr_assert(eq(sz, count_digits(nonempty_string), 2));
}

// Check that all digits are counted.
Test(count_digits, count_all_digits) {
  const char* digits = "0123456789";
  cr_assert(eq(sz, count_digits(digits), 10));
}
