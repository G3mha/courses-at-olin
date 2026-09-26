#include <pthread.h>      // pthread_*
#include <stdio.h>        // printf, perror
#include <stdlib.h>       // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdnoreturn.h>  // noreturn

enum { COUNT_LIMIT = 100, NUM_THREADS = 50 };

// Print all the numbers from 0 to some limit, along with an identifying char.
void* counter(void* arg) {
  // Fill this in.
  return NULL;
}

noreturn void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

int main(void) {
  int shared_val = 0;
  pthread_t counters[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i) {
    if (pthread_create(counters + i, NULL, counter, (void*)&shared_val)) {
      error_and_exit("Couldn't create thread");
    }
  }
  for (int i = 0; i < NUM_THREADS; ++i) {
    if (pthread_join(counters[i], NULL)) {
      error_and_exit("Couldn't join thread");
    }
  }

  printf("shared_val: %d\n", shared_val);
  return EXIT_SUCCESS;
}
