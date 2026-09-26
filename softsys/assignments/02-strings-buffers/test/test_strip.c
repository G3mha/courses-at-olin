#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/string_utils.h"

// There is nothing to strip from an empty string.
Test(strip, empty_string) {
  const char* src = "";
  char dst[1];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = "a";
  strip(src, dst, chars);
  cr_assert(eq(str, dst, ""));
}

// If the set of characters to strip is empty, the string is left alone.
Test(strip, empty_chars) {
  const char* src = "abc";
  char dst[4];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = "";
  strip(src, dst, chars);
  cr_assert(eq(str, dst, "abc"));
}

// If the characters to strip is null, strip on whitespace instead.
Test(strip, null_chars) {
  const char* src = " spacious ";
  char dst[9];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = NULL;
  strip(src, dst, chars);
  cr_assert(eq(str, dst, "spacious"));
}

// Remove consecurity, identical characters from the start/end.
Test(strip, repeated_strip_chars) {
  const char* src = "   spacious   ";
  char dst[9];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = " ";
  strip(src, dst, chars);
  cr_assert(eq(str, dst, "spacious"));
}

// Remove consecutive but different characters from the start/end.
Test(strip, multiple_strip_chars) {
  const char* src = "abc123abc";
  char dst[4];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = "abc";
  strip(src, dst, chars);
  cr_assert(eq(str, dst, "123"));
}

// Don't remove characters from the middle of the string.
Test(strip, middle_chars_preserved) {
  const char* src = "abc1abc2abc3abc";
  char dst[10];  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  const char* chars = "abc";
  strip(src, dst, chars);
  cr_assert(eq(str, dst, "1abc2abc3"));
}
