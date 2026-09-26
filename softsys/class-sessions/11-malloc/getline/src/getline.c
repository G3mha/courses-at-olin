#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>   // getline
#include <stdlib.h>  // EXIT_SUCCESS

int main(void) {
  char* line = NULL;
  size_t line_size = 0;
  puts("Enter some text:");
  if (getline(&line, &line_size, stdin) == -1) {
    return -1;
  }
  printf("You typed:\n%s", line);
  return EXIT_SUCCESS;
}
