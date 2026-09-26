#include "cache.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

const size_t ADDR_BITS = 64;

cache_line* make_line(size_t block_size) {
  cache_line* line = malloc(sizeof(cache_line));
  line->block = malloc(block_size * sizeof(byte));
  line->tag = 0;
  line->valid = 0;
  return line;
}

void free_line(cache_line* line) {
  free(line->block);
  free(line);
}

cache* make_cache(line_params params) {
  cache* cache_ = malloc(sizeof(cache));
  cache_->params = params;

  // Comput the number of lines and the line size to properly allocate the
  // memory for the lines.
  size_t num_lines = (size_t)1 << params.num_index_bits;
  size_t line_size = (size_t)1 << params.num_offset_bits;
  cache_->lines = malloc(num_lines * sizeof(cache_line*));
  for (size_t i = 0; i < num_lines; ++i) {
    cache_->lines[i] = make_line(line_size);
  }

  // Initialize the bookkeeping values.
  cache_->hits = 0;
  cache_->misses = 0;
  cache_->evictions = 0;

  return cache_;
}

void free_cache(cache* cache_) {
  for (size_t i = 0; i < ((size_t)1 << cache_->params.num_index_bits); ++i) {
    free_line(cache_->lines[i]);
  }
  free(cache_->lines);
  free(cache_);
}

uintptr_t get_tag(const byte* addr, line_params params) {
  size_t num_line_bits = params.num_index_bits + params.num_offset_bits;
  // If the number of line bits is zero, the entire address is the tag.
  if (!num_line_bits) {
    return (uintptr_t)addr;
  }
  size_t num_tag_bits = ADDR_BITS - num_line_bits;
  uintptr_t mask = ((uintptr_t)1 << num_tag_bits) - 1;
  // Bitwise operations don't work on pointers, and we need to return a
  // uintptr_t anyway, so cast it explicitly here.
  return ((uintptr_t)addr >> num_line_bits) & mask;
}

uintptr_t get_line_index(const byte* addr, line_params params) {
  uintptr_t mask = ((uintptr_t)1 << params.num_index_bits) - 1;
  // Bitwise operations don't work on pointers, and we need to return a
  // uintptr_t anyway, so cast it explicitly here.
  return ((uintptr_t)addr >> params.num_offset_bits) & mask;
}

uintptr_t get_line_offset(const byte* addr, line_params params) {
  if (params.num_offset_bits == ADDR_BITS) {
    return (uintptr_t)addr;
  }
  uintptr_t mask = ((uintptr_t)1 << params.num_offset_bits) - 1;
  // Bitwise operations don't work on pointers, and we need to return a
  // uintptr_t anyway, so cast it explicitly here.
  return (uintptr_t)addr & mask;
}

size_t block_size(const cache* cache_) {
  // If the number of offset bits happens to be the number of bits in a pointer,
  // Set the block size to its maximum. The block size will be off by one, but
  // in practice this is far more memory than modern systems have anyway.
  if (cache_->params.num_offset_bits == ADDR_BITS) {
    return SIZE_MAX;
  }
  return (size_t)1 << cache_->params.num_offset_bits;
}

// Both the load and store operations require checking whether a line is in the
// cache, and to load the line in if necessary. Do that here.
static void access(cache* cache_, const byte* addr) {
  uintptr_t tag = get_tag(addr, cache_->params);
  uintptr_t line_index = get_line_index(addr, cache_->params);
  cache_line* line = cache_->lines[line_index];
  if (line->valid == 1 && line->tag == tag) {
    ++cache_->hits;
  } else {
    // A cache eviction is also a cache miss. The valid bit tells us if there's
    // already memory loaded into the line, which is an eviction.
    ++cache_->misses;
    if (line->valid == 1) {
      ++cache_->evictions;
    }
    line->valid = 1;
    line->tag = tag;
    // The pointer being accessed may be in the middle of a line that is cached.
    // We can get the start of the line/block by subtracting out the offset and
    // then getting the appropriate number of bytes from memory.
    ptrdiff_t offset = (ptrdiff_t)get_line_offset(addr, cache_->params);
    const byte* block_addr = addr - offset;
    for (size_t i = 0; i < block_size(cache_); ++i) {
      line->block[i] = block_addr[i];
    }
  }
}

byte load(cache* cache_, const byte* addr) {
  access(cache_, addr);
  uintptr_t line_index = get_line_index(addr, cache_->params);
  uintptr_t line_offset = get_line_offset(addr, cache_->params);
  return cache_->lines[line_index]->block[line_offset];
}

void store(cache* cache_, byte* addr, byte value) {
  access(cache_, addr);
  uintptr_t line_index = get_line_index(addr, cache_->params);
  uintptr_t line_offset = get_line_offset(addr, cache_->params);
  cache_->lines[line_index]->block[line_offset] = value;
  // This cache does not have write-back functionality, so even though the value
  // was changed in the cache line, the memory at the given address needs to be
  // modified as well.
  *addr = value;
}
