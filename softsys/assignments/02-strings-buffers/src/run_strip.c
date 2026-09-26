#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

int main(void) {
  // Change these strings to test your implementation.
  const char* src = "a";
  const char* chars = "a";

  char* dst = (char*) malloc(strlen(src));
  strip(src, dst, chars);
  printf("strip(%s, dst, %s) is %s\n", src, chars, dst);
  free(dst);
  return 0;
}
