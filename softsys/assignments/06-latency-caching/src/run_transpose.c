#include <stdio.h>

#include "cache.h"
#include "transpose.h"

void run_test(byte* src_matrix, size_t height, size_t width, line_params params,
              void (*transpose_function)(const byte*, byte*, size_t, size_t,
                                         cache*)) {
  cache* cache_ = make_cache(params);
  // Transpose the height and width for the destination matrix. This triggers
  // clang-tidy, but we know what we're doing here.
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* dst_matrix = make_uninitialized_matrix(width, height);

  // It only makes sense to print out cache statistics if the transpose wasn't//
  // correct.
  transpose_function(src_matrix, dst_matrix, height, width, cache_);
  if (is_transpose(src_matrix, dst_matrix, height, width)) {
    puts("Matrix transposed correctly.");
    printf("Hits: %zu, Misses: %zu, Evictions: %zu\n", cache_->hits,
           cache_->misses, cache_->evictions);
  } else {
    puts("Matrix was not transposed correctly - no stats for this run.");
  }

  // Clean up.
  free_matrix(dst_matrix);
  free_cache(cache_);
}

int main(void) {
  // Change these if you want to do more testing.
  // Don't commit changes to this file.
  size_t height = 61;           // NOLINT(*-magic-numbers)
  size_t width = 67;            // NOLINT(*-magic-numbers)
  line_params params = {5, 3};  // NOLINT(*-magic-numbers)

  // Run the tests.
  byte* src_matrix = make_random_matrix(height, width);
  puts("Running reference transpose implementation.");
  run_test(src_matrix, height, width, params, transpose_ref);
  puts("Running test transpose implementation.");
  run_test(src_matrix, height, width, params, transpose);

  // Clean up.
  free_matrix(src_matrix);
  return 0;
}
