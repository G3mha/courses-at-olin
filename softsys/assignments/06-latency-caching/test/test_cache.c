#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdlib.h>

#include "../src/cache.h"

// NOLINTBEGIN(*-magic-numbers)

Test(make_line, line_invalid) {
  cache_line* line = make_line(4);
  cr_assert(zero(uint, line->valid));
}

Test(get_tag, upper_quarter) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {32, 16};
  cr_assert(eq(uptr, get_tag(addr, params), 0xfedc));
}

Test(get_tag, upper_half) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {12, 20};
  cr_assert(eq(uptr, get_tag(addr, params), 0xfedcba98));
}

Test(get_tag, upper_three_quarters) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {12, 4};
  cr_assert(eq(uptr, get_tag(addr, params), 0xfedcba987654));
}

Test(get_tag, all_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {0, 0};
  cr_assert(eq(uptr, get_tag(addr, params), (uintptr_t)addr));
}

Test(get_line_index, highest_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {16, 48};
  cr_assert(eq(uptr, get_line_index(addr, params), 0xfedc));
}

Test(get_line_index, higher_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {16, 32};
  cr_assert(eq(uptr, get_line_index(addr, params), 0xba98));
}

Test(get_line_index, lower_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {16, 16};
  cr_assert(eq(uptr, get_line_index(addr, params), 0x7654));
}

Test(get_line_index, lowest_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {16, 0};
  cr_assert(eq(uptr, get_line_index(addr, params), 0x3210));
}

Test(get_line_offset, lower_quarter) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {0, 16};
  cr_assert(eq(uptr, get_line_offset(addr, params), 0x3210));
}

Test(get_line_offset, lower_half) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {0, 32};
  cr_assert(eq(uptr, get_line_offset(addr, params), 0x76543210));
}

Test(get_line_offset, lower_three_quarters) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {0, 48};
  cr_assert(eq(uptr, get_line_offset(addr, params), 0xba9876543210));
}

Test(get_line_offset, all_bytes) {
  byte* addr = (byte*)0xfedcba9876543210;
  line_params params = {0, 64};
  cr_assert(eq(uptr, get_line_offset(addr, params), (uintptr_t)addr));
}

Test(load, read_value) {
  byte test_byte = 0xff;
  line_params params = {16, 4};
  cache* cache_ = make_cache(params);
  cr_assert(eq(u8, load(cache_, &test_byte), test_byte));
  free_cache(cache_);
}

Test(store, write_new_value) {
  byte test_byte = 0x0;
  line_params params = {16, 4};
  cache* cache_ = make_cache(params);
  store(cache_, &test_byte, 0xff);
  cr_assert(eq(u8, test_byte, 0xff));
  free_cache(cache_);
}

// NOLINTNEXTLINE(*-todo)
// TODO: add other tests.

// NOLINTEND(*-magic-numbers)
