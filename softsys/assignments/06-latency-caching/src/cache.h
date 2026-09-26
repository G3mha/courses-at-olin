#pragma once

#include <stddef.h>
#include <stdint.h>

// Set the type of a byte and its maximum value.
typedef uint8_t byte;
#define BYTE_MAX UINT8_MAX

// The number of address bits needs to be unsigned to make bitwise manipulation
// work out. An enum only stores ints (until C23) so define it here as an
// external constant.
extern const size_t ADDR_BITS;

// A cache line.
typedef struct {
  /// The bytes stored in this line.
  byte* block;
  /// The tag used to determine which address of memory is in this line.
  uintptr_t tag;
  /// A bit indicating if memory is stored in this line.
  unsigned int valid : 1;
} cache_line;

// Parameters for the cache line and offset size.
typedef struct {
  /// The number of bits used to index a cache line.
  size_t num_index_bits;
  /// The number of bits used to index an offset into the cache line.
  size_t num_offset_bits;
} line_params;

// The cache itself.
typedef struct {
  /// The actual cache lines of this cache
  cache_line** lines;
  /// The line index and offset parameters used in this cache.
  line_params params;
  /// The number of cache hits so far.
  size_t hits;
  /// The number of cache misses so far.
  size_t misses;
  /// The number of cache evictions so far.
  size_t evictions;
} cache;

/**
 * Allocate memory for a single line in the cache.
 *
 * Given a specific number of bytes, create a cache line of the appropriate size
 * on the heap. The caller is responsible for ensuring that the memory is
 * cleaned up after use.
 *
 * @param block_size The number of bytes in the line.
 * @return A pointer to the cache line.
 */
cache_line* make_line(size_t block_size);

/**
 * Free memory for a single line in the cache.
 *
 * @param line A pointer to the cache line to free.
 */
void free_line(cache_line* line);

/**
 * Make a cache with a given set of parameters.
 *
 * Given a set of parameters representing a number of lines and the size of
 * each line, dynamically allocate a direct-mapped cache. The caller is
 * responsible for ensuring that the memory is cleaned up after use.
 *
 * @param params Parameters used to set the number of lines and line size.
 * @return A pointer to the new cache.
 */
cache* make_cache(line_params params);

/**
 * Free memory for a cache.
 *
 * @param cache_ A pointer to the cache to free.
 */
void free_cache(cache* cache_);

/**
 * Get the tag bits of an address.
 *
 * Given an address and a set of cache parameters indicating the number of bits
 * used for the line index and line offset, extract and return the tag bits. The
 * tag bits are defined as the most significant bits of the address, with the
 * exact width dependent on the cache parameters. The tag bits are returns as
 * the least significant bits of the return value to facilitate cache line
 * lookup.
 *
 * @param addr The address to look up in the cache.
 * @param params A pair representing the number of cache line and offset bits.
 * @return A pointer whose least significant bits are the tag bits.
 */
uintptr_t get_tag(const byte* addr, line_params params);

/**
 * Get the line index bits of an address.
 *
 * Given an address and a set of cache parameters indicating the number of bits
 * used for the line index and line offset, extract and return the line index
 * bits. The line index bits are defined as the middle bits of the address,
 * between the tag and the line offset bits, with the exact width dependent on
 * the relevant cache parameter. The bits are returned as the least significant
 * bits of the return value to facilitate cache line lookup.
 *
 * @param addr The address to look up in the cache.
 * @param params A pair representing the number of cache line and offset bits.
 * @return A pointer whose least significant bits are the line index bits.
 */
uintptr_t get_line_index(const byte* addr, line_params params);

/**
 * Get the line offset bits of an address.
 *
 * Given an address and a set of cache parameters indicating the number of bits
 * used for the line index and line offset, extract and return the line offset
 * bits. The line offset bits are defined as the lowest bits of the address,
 * with the exact width dependent on the relevant cache parameter. The bits are
 * returned as the least significant bits of the return value to facilitate
 * cache offset lookup.
 *
 * @param addr The address to look up in the cache.
 * @param params A pair representing the number of cache line and offset bits.
 * @return A pointer whose least significant bits are the line offset bits.
 */
uintptr_t get_line_offset(const byte* addr, line_params params);

/**
 * Get the size of a line of the cache in bytes.
 *
 * Given a cache, use its parameters to compute the size of a single cache line
 * in bytes. This function is provided because the cache line size is stored
 * as the number of bits to represent the offset (the log base 2 of the line
 * size in bytes).
 *
 * @param cache_ A pointer to the cache.
 * @return The line size in bytes.
 */
size_t block_size(const cache* cache_);

/**
 * Load a byte from an address in memory, going through the cache.
 *
 * Given a cache and a byte address, retrieve the byte at that address by
 * querying the cache. If the relevant line is in the cache, the cache should
 * return the byte from that line and register a cache hit. Otherwise, the cache
 * registers a cache miss and loads the relevant line into the cache. If
 * necessary, the cache should also evict a line at the given position,
 * registering a cache eviction as necessary.
 *
 * @param cache_ The cache to go through.
 * @param addr The address of a desired byte.
 * @return The byte at addr.
 */
byte load(cache* cache_, const byte* addr);

/**
 * Store a byte to an address in memory, going through the cache.
 *
 * Given a cache and a byte address, write a given value to the byte at that
 * address by querying the cache. If the relevant line is in the cache, the
 * cache should write the byte from that line and register a cache hit.
 * Otherwise, the cache registers a cache miss and loads the relevant line into
 * the cache. If necessary, the cache should also evict a line at the given
 * position, registering a cache eviction as necessary.
 *
 * @param cache_ The cache to go through.
 * @param addr The address of a desired byte.
 * @param value The value to write to addr.
 */
void store(cache* cache_, byte* addr, byte value);
