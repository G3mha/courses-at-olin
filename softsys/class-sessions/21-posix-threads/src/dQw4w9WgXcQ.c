#include <pthread.h>      // pthread_*
#include <semaphore.h>    // sem_*
#include <stdio.h>        // printf, perror
#include <stdlib.h>       // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdnoreturn.h>  // noreturn

enum { COUNT_LIMIT = 100, NUM_THREADS = 50 };

void* first(void* arg) {
  // Fill this in.
  puts("Never gonna");
  pthread_exit(NULL);
}

void* second(void* arg) {
  // Fill this in.
  puts("give you up");
  pthread_exit(NULL);
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
