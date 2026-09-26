#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdlib.h>

#include "../src/string_utils.h"

void make_string_space(char* buffer[], size_t buffer_size, size_t string_size) {
  for (size_t i = 0; i < buffer_size - 1; ++i) {
    buffer[i] = malloc(string_size * sizeof(char));
  }
}

void free_string_space(char* buffer[], size_t buffer_size) {
  for (size_t i = 0; i < buffer_size - 1; ++i) {
    free(buffer[i]);
  }
}

// Splitting an empty string should return an array containing just the empty
// string.
Test(split, split_empty_string) {
  const char* src = "";
  char* dst[2];
  make_string_space(dst, 2, 1);
  const char* sep = "a";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], ""));
  cr_assert(eq(ptr, dst[1], NULL));
  free_string_space(dst, 2);
}

// If the separator isn't in the string at all, the array contains just the
// string.
Test(split, sep_not_found) {
  const char* src = "abc";
  char* dst[2];
  make_string_space(dst, 2, strlen(src) + 1);
  const char* sep = "d";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "abc"));
  cr_assert(eq(ptr, dst[1], NULL));
  free_string_space(dst, 2);
}

// Splitting a string into multiple tokens should work.
Test(split, basic_split) {
  char* src = "raindrops,roses,whiskers on kittens";
  char* dst[4];
  make_string_space(dst, 4, 20);
  const char* sep = ",";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "raindrops"));
  cr_assert(eq(str, dst[1], "roses"));
  cr_assert(eq(str, dst[2], "whiskers on kittens"));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}

// Consecutive separators should result in an empty string in the array.
Test(split, consecutive_sep) {
  const char* src = "abc,,123";
  char* dst[4];
  make_string_space(dst, 4, 4);
  const char* sep = ",";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "abc"));
  cr_assert(eq(str, dst[1], ""));
  cr_assert(eq(str, dst[2], "123"));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}

// If the string starts with a separator, there should be an empty string at the
// beginning of the array.
Test(split, beginning_sep) {
  const char* src = ",abc,123";
  char* dst[4];
  make_string_space(dst, 4, 4);
  const char* sep = ",";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], ""));
  cr_assert(eq(str, dst[1], "abc"));
  cr_assert(eq(str, dst[2], "123"));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}

// If the string ends with a separator, there should be an empty string at the
// end of the array (before the null pointer).
Test(split, end_sep) {
  const char* src = "abc,123,";
  char* dst[4];
  make_string_space(dst, 4, 4);
  const char* sep = ",";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "abc"));
  cr_assert(eq(str, dst[1], "123"));
  cr_assert(eq(str, dst[2], ""));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}

// Split a string with a multicharacter separator.
Test(split, multichar_sep) {
  const char* src = "1<>2<>3";
  char* dst[4];
  make_string_space(dst, 4, 2);
  const char* sep = "<>";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "1"));
  cr_assert(eq(str, dst[1], "2"));
  cr_assert(eq(str, dst[2], "3"));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}

// Split a string with a separator involving repeated characters. This checks
// that overlapping separators are not counted twice.
Test(split, repeated_char_sep) {
  const char* src = "1...2...3";
  char* dst[4];
  make_string_space(dst, 4, 3);
  const char* sep = "..";
  split(src, dst, sep);
  cr_assert(eq(str, dst[0], "1"));
  cr_assert(eq(str, dst[1], ".2"));
  cr_assert(eq(str, dst[2], ".3"));
  cr_assert(eq(ptr, dst[3], NULL));
  free_string_space(dst, 4);
}
