#include <stdio.h>
#include <stdlib.h>

// This program doesn't use command-line arguments, so the main function should
// take no arguments.
int main(void) {
  puts("Hello world!");
  // We could also return 0 here and not include stdlib.h, but explicitly
  // returning EXIT_SUCCESS is bit more intuitive.
  return EXIT_SUCCESS;
}