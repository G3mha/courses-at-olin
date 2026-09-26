#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/weave.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

// Check that a single thread prints its lines in the correct order.
Test(start_threads, single_thread, .init = cr_redirect_stdout) {
  start_threads(1);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Thread 0 ready!\nThread 0 go!\n");
}

// Check that all threads produce output.
Test(start_threads, all_threads, .init = cr_redirect_stdout) {
  FILE* redirected_stdout = cr_get_redirected_stdout();
  size_t num_threads = 42;
  start_threads(num_threads);
  (void)fflush(stdout);
  int* printed_output = calloc(num_threads, sizeof(int));
  char* line = NULL;
  size_t line_len = 0;
  while (getline(&line, &line_len, redirected_stdout) != -1) {
    // Skip the first word in the line, then get the thread ID from the second.
    (void)strtok(line, " ");
    int thread_id = (int)strtol(strtok(NULL, " "), NULL, 10);

    // Mark that this thread has printed its output.
    printed_output[thread_id] = 1;
    free(line);
    line = NULL;
  }
  free(line);
  // cr_expect(not(zero(int, feof(redirected_stdout))));
  for (size_t i = 0; i < num_threads; ++i) {
    cr_expect(eq(int, printed_output[i], 1));
  }
  free(printed_output);
}

// Check that no thread prints go before all threads have printed ready.
Test(start_threads, ready_before_go, .init = cr_redirect_stdout) {
  FILE* redirected_stdout = cr_get_redirected_stdout();
  size_t num_threads = 42;
  start_threads(num_threads);
  (void)fflush(stdout);
  size_t ready_threads = 0;
  char* line = NULL;
  size_t line_len = 0;
  while (getline(&line, &line_len, redirected_stdout) != -1) {
    // Get the last word in the output, which is "ready!" or "go!".
    (void)strtok(line, " ");
    (void)strtok(NULL, " ");
    char* method = strtok(NULL, " \n");

    // Count the number of ready threads until we see a "go!"
    if (strcmp(method, "ready!") == 0) {
      ++ready_threads;
    } else if (strcmp(method, "go!") == 0) {
      // We only need to check once - if all threads are ready, then the test
      // passes, and if not, the test fails.
      cr_expect(eq(sz, ready_threads, num_threads));
      break;
    }
    free(line);
    line = NULL;
  }
  free(line);
}

// TODO: Add more tests checking the contents of stdout

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
