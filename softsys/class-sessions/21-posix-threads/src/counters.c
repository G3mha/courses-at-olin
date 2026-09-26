#include <pthread.h>      // pthread_*
#include <stdio.h>        // printf, perror
#include <stdlib.h>       // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdnoreturn.h>  // noreturn

enum { COUNT_LIMIT = 100 };

// Print all the numbers from 0 to some limit, along with an identifying char.
void* counter(void* counter_name) {
  for (int i = 0; i < COUNT_LIMIT; ++i) {
    printf("%c: %d\n", *(char*)counter_name, i);
  }
  return NULL;
}

noreturn void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

int main(void) {
  // Fill this in.
  return EXIT_SUCCESS;
}
