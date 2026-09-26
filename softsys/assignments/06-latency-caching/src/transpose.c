#include "transpose.h"

#include <stdlib.h>

#include "cache.h"

byte* make_uninitialized_matrix(size_t height, size_t width) {
  // Since we're not placing any values in the matrix, we can just return the
  // memory as is.
  return malloc(height * width * sizeof(byte));
}

byte* make_random_matrix(size_t height, size_t width) {
  byte* matrix = make_uninitialized_matrix(height, width);
  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      // NOLINTNEXTLINE(cert-msc30-c)
      *get_addr(matrix, width, row, col) = (byte)(rand() % BYTE_MAX);
    }
  }
  return matrix;
}

void free_matrix(byte* matrix) {
  // The matrix is implemented as a single block of memory, so it can be freed
  // all at once.
  free(matrix);
}

byte* get_addr(const byte* matrix, size_t width, size_t row, size_t col) {
  // matrix is marked as constant to avoid accidental changes, so explicitly
  // case it to a non-const address here.
  return (byte*)matrix + row * width + col;
}

int is_transpose(const byte* lhs, const byte* rhs, size_t height,
                 size_t width) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      // NOLINTNEXTLINE(readability-suspicious-call-argument)
      if (*get_addr(lhs, width, row, col) != *get_addr(rhs, height, col, row)) {
        return 0;
      }
    }
  }
  return 1;
}

void transpose_ref(const byte* src, byte* dst, size_t height, size_t width,
                   cache* cache_) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      const byte* src_addr = get_addr(src, width, row, col);
      // NOLINTNEXTLINE(readability-suspicious-call-argument)
      byte* dst_addr = get_addr(dst, height, col, row);
      // Make sure to load and store using the cache.
      byte src_byte = load(cache_, src_addr);
      store(cache_, dst_addr, src_byte);
    }
  }
}

void transpose(const byte* src, byte* dst, size_t height, size_t width,
               cache* cache_) {
  // Write your implementation here.
  // USE load() AND store() - DON'T ACCESS MEMORY DIRECTLY.
}
