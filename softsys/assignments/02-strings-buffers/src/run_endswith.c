#include <stdio.h>

#include "string_utils.h"

int main(void) {
  // Change these strings to test your implementation.
  const char* str = "";
  const char* substr = "";
  printf("endswith(%s, %s) is %d\n", str, substr, endswith(str, substr));
  return 0;
}
