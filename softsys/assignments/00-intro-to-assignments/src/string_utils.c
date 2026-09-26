#include "string_utils.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

size_t string_length(const char* str) {
  size_t length = 0;
  const char* position = str;
  while (*position != '\0') {
    ++length;
    ++position;
  }
  return length;
}

size_t count_vowels(const char* text) {
  size_t num_vowels = 0;
  const char* vowels = "AEIOUaeiou";
  for (size_t i = 0; i < strlen(text); ++i) {
    if (strchr(vowels, text[i])) {
      ++num_vowels;
    }
  }
  return num_vowels;
}

size_t count_digits(const char* text) {
  size_t num_digits = 0;
  // NOLINTNEXTLINE
  for (size_t i = 0; i < strlen(text); ++i) {
    if (isdigit(text[i])) {
      ++num_digits;
    }
  }
  return num_digits;
}
