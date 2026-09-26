#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

int main(void) {
  // Change these strings to test your implementation.
  const char* src = "a";
  const char* sep = "";
  
  size_t src_len = strlen(src);
  char** dst = (char**) malloc(src_len);
  for (size_t i = 0; i < src_len; ++i) {
    dst[i] = (char*) malloc(src_len);
  }
  split(src, dst, sep);
  printf("split(%s, dst, %s) is %s\n", src, sep, dst);
  for (size_t i = 0; i < src_len; ++i) {
    free(dst[i]);
  }
  free(dst);
  return 0;
}
