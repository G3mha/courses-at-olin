#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <inttypes.h>
#include <stdlib.h>

#include "../src/cache.h"
#include "../src/transpose.h"

// NOLINTBEGIN(*-magic-numbers,cert-msc30-c,cert-msc32-c)

// No tests needed for an uninitialized matrix.

// Check that the matrix is created correctly.
Test(make_random_matrix, small) {
  srand(42);
  byte* matrix = make_random_matrix(2, 2);
  srand(42);
  cr_expect(eq(u8, *get_addr(matrix, 2, 0, 0), rand() % BYTE_MAX));
  cr_expect(eq(u8, *get_addr(matrix, 2, 0, 1), rand() % BYTE_MAX));
  cr_expect(eq(u8, *get_addr(matrix, 2, 1, 0), rand() % BYTE_MAX));
  cr_expect(eq(u8, *get_addr(matrix, 2, 1, 1), rand() % BYTE_MAX));
  free_matrix(matrix);
}

// Test that the reference implementation of the transpose works correctly.
Test(is_transpose, reference) {
  srand(42);
  size_t height = 32;
  size_t width = 32;
  byte* src = make_random_matrix(height, width);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* dst = make_uninitialized_matrix(width, height);
  line_params params = {5, 5};
  cache* cache_ = make_cache(params);
  transpose_ref(src, dst, height, width, cache_);
  cr_expect(eq(int, is_transpose(src, dst, height, width), 1));
  free_cache(cache_);
  free_matrix(src);
  free_matrix(dst);
}

// Test that the transpose function was implemented correctly. This test must
// pass to receive credit.
Test(is_transpose, test) {
  srand(42);
  size_t height = 32;
  size_t width = 32;
  byte* src = make_random_matrix(height, width);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* dst = make_uninitialized_matrix(width, height);
  line_params params = {5, 5};
  cache* cache_ = make_cache(params);
  transpose(src, dst, height, width, cache_);
  cr_expect(eq(int, is_transpose(src, dst, height, width), 1));
  free_cache(cache_);
  free_matrix(src);
  free_matrix(dst);
}

Test(transpose, better_than_reference) {
  srand(42);
  size_t height = 61;
  size_t width = 67;
  line_params params = {5, 3};
  byte* src = make_random_matrix(height, width);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* ref_dst = make_uninitialized_matrix(width, height);
  cache* ref_cache = make_cache(params);
  transpose_ref(src, ref_dst, height, width, ref_cache);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* test_dst = make_uninitialized_matrix(width, height);
  cache* test_cache = make_cache(params);
  transpose(src, test_dst, height, width, test_cache);
  cr_expect(gt(sz, test_cache->hits, ref_cache->hits));
  cr_expect(lt(sz, test_cache->misses, ref_cache->misses));
  cr_expect(lt(sz, test_cache->evictions, ref_cache->evictions));
  free_matrix(src);
  free_matrix(ref_dst);
  free_cache(ref_cache);
  free_matrix(test_dst);
  free_cache(test_cache);
}

Test(transpose, significant_improvement) {
  srand(42);
  size_t height = 61;
  size_t width = 67;
  line_params params = {5, 3};
  byte* src = make_random_matrix(height, width);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* ref_dst = make_uninitialized_matrix(width, height);
  cache* ref_cache = make_cache(params);
  transpose_ref(src, ref_dst, height, width, ref_cache);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* test_dst = make_uninitialized_matrix(width, height);
  cache* test_cache = make_cache(params);
  transpose(src, test_dst, height, width, test_cache);
  for (size_t threshold = 100; threshold <= 600; threshold += 50) {
    cr_expect(lt(sz, test_cache->misses + threshold, ref_cache->misses));
  }
  free_matrix(src);
  free_matrix(ref_dst);
  free_cache(ref_cache);
  free_matrix(test_dst);
  free_cache(test_cache);
}

Test(transpose, extra_credit) {
  srand(42);
  size_t height = 61;
  size_t width = 67;
  line_params params = {5, 3};
  byte* src = make_random_matrix(height, width);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* ref_dst = make_uninitialized_matrix(width, height);
  cache* ref_cache = make_cache(params);
  transpose_ref(src, ref_dst, height, width, ref_cache);
  // NOLINTNEXTLINE(readability-suspicious-call-argument)
  byte* test_dst = make_uninitialized_matrix(width, height);
  cache* test_cache = make_cache(params);
  transpose(src, test_dst, height, width, test_cache);
  size_t ref_misses = ref_cache->misses;
  size_t test_misses = test_cache->misses;
  free_matrix(src);
  free_matrix(ref_dst);
  free_cache(ref_cache);
  free_matrix(test_dst);
  free_cache(test_cache);
  if (test_misses + 1100 > ref_misses) {
    cr_skip(
        "No extra credit since number of cache misses is %zu compared to "
        "reference %zu (must beat by at least 1100 to qualify)\n",
        test_misses, ref_misses);
  }
  cr_fail("IGNORE THIS FAILURE");
  cr_fail("Extra credit: %zu points\n", (ref_misses - test_misses - 600) / 500);
}

// NOLINTNEXTLINE(*-todo)
// TODO: add more tests

// NOLINTEND(*-magic-numbers,cert-msc30-c,cert-msc32-c)
