#include <stdio.h>

#include "string_utils.h"

int main(void) {
  // Change these strings to test your implementation.
  const char* str = "";
  const char* substr = "";
  printf("count(%s, %s) is %zu\n", str, substr, count(str, substr));
  return 0;
}
