#pragma once

#include <stdlib.h>

#include "cache.h"

/**
 * Create an uninitalized matrix of a given size.
 *
 * Create a dynamically allocated matrix of a given height (number of rows) and
 * width (number of columns). The caller is responsible for ensuring that the
 * matrix is cleaned up after use.
 *
 * @param height The number of rows in the new matrix.
 * @param width The number of columns in the new matrix.
 * @return A pointer to the location of the new matrix.
 */
byte* make_uninitialized_matrix(size_t height, size_t width);

/**
 * Create an matrix of a given size filled with random values.
 *
 * Create a dynamically allocated matrix of a given height (number of rows) and
 * width (number of columns). All entries of the matrix are pseudorandomly
 * generated. The values are not guaranteed to be suitably random for
 * statistical or cryptographic use. The caller is responsible for ensuring that
 * the matrix is cleaned up after use.
 *
 * @param height The number of rows in the new matrix.
 * @param width The number of columns in the new matrix.
 * @return A pointer to the location of the new matrix.
 */
byte* make_random_matrix(size_t height, size_t width);

/**
 * Free memory allocated for a matrix.
 *
 * Given a dynamically allocated matrix, free the memory associated with the
 * matrix.
 *
 * @param matrix A pointer to the matrix to free.
 */
void free_matrix(byte* matrix);

/**
 * Get the address of a specific entry in a matrix.
 *
 * Given a row and column index of a matrix, get the address of the byte
 * at that entry. The width of the matrix is required to compute the correct
 * address. No bounds checking on either the row or column is performed.
 *
 * @param matrix The matrix in which to receive a value.
 * @param width The number of columns in the matrix.
 * @param row The row index of the entry to retrieve.
 * @param col The column index of the entry to retrieve.
 * @return The address of the byte at the given entry.
 */
byte* get_addr(const byte* matrix, size_t width, size_t row, size_t col);

/**
 * Check whether two matrices are transposes of each other.
 *
 * @param lhs One of the matrices to check.
 * @param rhs The other matrix to check.
 * @param height The number of rows in lhs.
 * @param width The number of columns in lhs.
 * @return 1 if the matrices are transposes and 0 otherwise.
 */
int is_transpose(const byte* lhs, const byte* rhs, size_t height, size_t width);

/**
 * Transpose a matrix, using a cache as necessary. (Reference implementation.)
 *
 * See documentation for transpose.
 */
void transpose_ref(const byte* src, byte* dst, size_t height, size_t width,
                   cache* cache_);

/**
 * Transpose a matrix, using a cache as necessary.
 *
 * Given a matrix, transpose the entries, essentially mirroring it along the
 * diagonal. After transposition, dst[j][i] should be src[i][j] for all valid
 * indices i and j. The called is responsible for allocating the appropriate
 * amount of memory for the destination matrix, so no bounds checking is done.
 *
 * @param src The matrix to transpose.
 * @param dst The matrix in which to write the transposed entries.
 * @param height The number of row in src.
 * @param width The number of columns in src.
 * @param cache_ The cache to use.
 */
void transpose(const byte* src, byte* dst, size_t height, size_t width,
               cache* cache_);
