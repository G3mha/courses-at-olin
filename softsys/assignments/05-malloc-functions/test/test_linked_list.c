#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdlib.h>

#include "../src/linked_list.h"

// NOLINTBEGIN(*-magic-numbers)

// When making a node, the value should be set correctly.
Test(make_node, value_set_correctly) {
  node* node_ = make_node(42);
  cr_assert(eq(int, node_->val, 42));
  free_node(node_);
}

// Making a new node should set the next node to the null pointer by default.
Test(make_node, next_is_null) {
  node* node_ = make_node(42);
  cr_assert(eq(ptr, node_->next, NULL));
  free_node(node_);
}

// There aren't good, reliable ways to check free_node other than Valgrind, so
// don't add any unit tests for free_node.

// Making a new list should create an empty list, so the head should be the null
// pointer.
Test(make_list, null_head) {
  list* list_ = make_list();
  cr_assert(zero(ptr, list_->head));
  free_list(list_);
}

// Making a new list should create an empty list, so the length should be 0.
Test(make_list, zero_len) {
  list* list_ = make_list();
  cr_assert(zero(sz, list_->len));
  free_list(list_);
}

// Copying a list should result in a new, distinct address for the copy.
Test(copy, different_list_address) {
  list* list_ = make_list();
  list* copy_ = copy(list_);
  cr_assert(ne(ptr, copy_, list_));
  free_list(list_);
  free_list(copy_);
}

// Copying a list should result in distinct addresses for all nodes in both
// lists.
Test(copy, different_node_address) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* copy_ = copy(list_);
  node* list_node = list_->head;
  node* copy_node = copy_->head;
  while (list_node != NULL) {
    cr_assert(ne(ptr, list_node, copy_node));
    list_node = list_node->next;
    copy_node = copy_node->next;
  }
  free_list(list_);
  free_list(copy_);
}

// Copying an empty list should result in the same length (0) for both lists.
Test(copy, same_len_empty) {
  list* list_ = make_list();
  list* copy_ = copy(list_);
  cr_assert(eq(sz, copy_->len, list_->len));
  free_list(list_);
  free_list(copy_);
}

// Copying a nonempty list should result in the same length for both lists.
Test(copy, same_len_nonempty) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* copy_ = copy(list_);
  cr_assert(eq(sz, copy_->len, list_->len));
  free_list(list_);
  free_list(copy_);
}

// Copying a list should result in the same values in the same order for both
// lists.
Test(copy, same_value) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* copy_ = copy(list_);
  for (size_t i = 0; i < list_->len; ++i) {
    cr_assert(eq(int, get(copy_, i, NULL), get(list_, i, NULL)));
  }
  free_list(list_);
  free_list(copy_);
}

// There aren't good, reliable ways to check free_list other than Valgrind, so
// don't add any unit tests for free_list.

// Getting any index from an empty list should return 0.
Test(get, empty_zero) {
  list* list_ = make_list();
  cr_assert(zero(int, get(list_, 0, NULL)));
  free_list(list_);
}

// Getting any index from an empty list should set the status to failure.
Test(get, empty_failure) {
  list* list_ = make_list();
  int status = 1;
  (void)get(list_, 0, &status);
  cr_assert(zero(int, status));
  free_list(list_);
}

// Getting an out of bounds index from a list should return 0.
Test(get, out_of_bounds_zero) {
  list* list_ = make_list();
  append(list_, 1);
  cr_assert(zero(int, get(list_, 1, NULL)));
  free_list(list_);
}

// Getting an out of bounds index from a list should set the status to
// failure.
Test(get, out_of_bounds_failure) {
  list* list_ = make_list();
  append(list_, 1);
  int status = 1;
  (void)get(list_, 1, &status);
  cr_assert(zero(int, status));
  free_list(list_);
}

// Getting an in bounds index from a list should return the appropriate
// value.
Test(get, in_bounds_value) {
  list* list_ = make_list();
  append(list_, 1);
  cr_assert(eq(int, get(list_, 0, NULL), 1));
  free_list(list_);
}

// Getting an in bounds index from a list should set the status to success.
Test(get, in_bounds_success) {
  list* list_ = make_list();
  append(list_, 1);
  int status = 0;
  (void)get(list_, 0, &status);
  cr_assert(eq(int, status, 1));
  free_list(list_);
}

// Empty lists should be equal.
Test(equal, empty_lists_equal) {
  list* lhs = make_list();
  list* rhs = make_list();
  cr_assert(eq(int, equal(lhs, rhs), 1));
  free_list(lhs);
  free_list(rhs);
}

// Any nonempty list should be equal to itself.
Test(equal, reflexive_list) {
  list* list_ = make_list();
  append(list_, 1);
  cr_assert(eq(int, equal(list_, list_), 1));
  free_list(list_);
}

// Two lists with different lengths should not be equal.
Test(equal, different_lengths) {
  list* lhs = make_list();
  list* rhs = make_list();
  append(rhs, 1);
  cr_assert(zero(int, equal(lhs, rhs)));
  free_list(lhs);
  free_list(rhs);
}

// Two lists with the same lengths and different elements should not be equal.
Test(equal, different_elements) {
  list* lhs = make_list();
  append(lhs, 0);
  list* rhs = make_list();
  append(rhs, 1);
  cr_assert(zero(int, equal(lhs, rhs)));
  free_list(lhs);
  free_list(rhs);
}

// Two lists with the same elements in different orders should not be equal.
Test(equal, different_element_order) {
  list* lhs = make_list();
  append(lhs, 1);
  append(lhs, 2);
  append(lhs, 3);
  list* rhs = make_list();
  append(rhs, 1);
  append(rhs, 3);
  append(rhs, 2);
  cr_assert(zero(int, equal(lhs, rhs)));
  free_list(lhs);
  free_list(rhs);
}

// Two lists with the same elements in the same order should be equal.
Test(equal, list_copy) {
  list* lhs = make_list();
  append(lhs, 1);
  append(lhs, 2);
  append(lhs, 3);
  list* rhs = copy(lhs);
  cr_assert(eq(int, equal(lhs, rhs), 1));
  free_list(lhs);
  free_list(rhs);
}

// Reversing an empty list should result in the same list.
Test(reverse, empty) {
  list* list_ = make_list();
  list* orig = copy(list_);
  reverse(list_);
  cr_assert(eq(int, equal(list_, orig), 1));
  free_list(list_);
  free_list(orig);
}

// Reversing a list with one element should result in the same list.
Test(reverse, singleton) {
  list* list_ = make_list();
  append(list_, 1);
  list* orig = copy(list_);
  reverse(list_);
  cr_assert(eq(int, equal(list_, orig), 1));
  free_list(list_);
  free_list(orig);
}

// Reversing a list should not change the number of elements.
Test(reverse, same_length) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* orig = copy(list_);
  reverse(list_);
  cr_assert(eq(sz, list_->len, orig->len));
  free_list(list_);
  free_list(orig);
}

// Reversing a list should modify the original list.
Test(reverse, modify_in_place) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* orig = copy(list_);
  reverse(list_);
  cr_assert(zero(int, equal(list_, orig)));
  free_list(list_);
  free_list(orig);
}

// Reversing a list should actually reverse the list.
Test(reverse, reverse_elements) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  reverse(list_);
  cr_assert(eq(int, get(list_, 0, NULL), 3));
  cr_assert(eq(int, get(list_, 1, NULL), 2));
  cr_assert(eq(int, get(list_, 2, NULL), 1));
  free_list(list_);
}

// Appending to a list should increase the length by one.
Test(append, increment_length) {
  list* list_ = make_list();
  cr_assert(zero(sz, list_->len));
  append(list_, 1);
  cr_assert(eq(sz, list_->len, 1));
  free_list(list_);
}

// Appending to a list should add the correct value at the correct index.
Test(append, correct_value_added) {
  list* setup_list = make_list();
  append(setup_list, 1);
  append(setup_list, 2);
  append(setup_list, 3);
  list* list_ = copy(setup_list);
  append(list_, 4);
  cr_assert(eq(int, get(list_, 3, NULL), 4));
  free_list(list_);
  free_list(setup_list);
}

// Appending to a list should not change any other value in the list.
Test(append, no_other_values_changed) {
  list* setup_list = make_list();
  append(setup_list, 1);
  append(setup_list, 2);
  append(setup_list, 3);
  list* list_ = copy(setup_list);
  append(list_, 4);
  cr_assert(eq(int, get(list_, 0, NULL), 1));
  cr_assert(eq(int, get(list_, 1, NULL), 2));
  cr_assert(eq(int, get(list_, 2, NULL), 3));
  free_list(list_);
  free_list(setup_list);
}

// Filter condition function that always returns true.
static int always_true(int num) {
  // num is unused here; cast it to avoid an unused parameter warning.
  (void)num;
  return 1;
}

// Filter condition function that always returns false.
static int always_false(int num) {
  // num is unused here; cast it to avoid an unused parameter warning.
  (void)num;
  return 0;
}

// Filter condition function that checks whether its input is odd.
static int is_odd(int num) { return num % 2; }

// Filtering an empty list should result in an empty list.
Test(filter, empty_list_stays_empty) {
  list* list_ = make_list();
  list* filtered_always_true = filter(list_, always_true);
  cr_assert(eq(int, equal(filtered_always_true, list_), 1));
  free_list(filtered_always_true);
  list* filtered_always_false = filter(list_, always_false);
  cr_assert(eq(int, equal(filtered_always_false, list_), 1));
  free_list(filtered_always_false);
  list* filtered_is_odd = filter(list_, is_odd);
  cr_assert(eq(int, equal(filtered_is_odd, list_), 1));
  free_list(filtered_is_odd);
  free_list(list_);
}

// Filtering a list where everything is true should result in the same list.
Test(filter, true_filter_copies_list) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* filtered_list = filter(list_, always_true);
  cr_assert(eq(int, equal(filtered_list, list_), 1));
  free_list(filtered_list);
  free_list(list_);
}

// Filtering a list where everything is false should result in an empty list.
Test(filter, false_filter_empties_list) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* filtered_list = filter(list_, always_false);
  list* empty_list = make_list();
  cr_assert(eq(int, equal(filtered_list, empty_list), 1));
  free_list(empty_list);
  free_list(filtered_list);
  free_list(list_);
}

// Filtering a list should include the correct items in the new list.
Test(filter, filter_elements) {
  list* list_ = make_list();
  append(list_, 1);
  append(list_, 2);
  append(list_, 3);
  list* expected_list = make_list();
  append(expected_list, 1);
  append(expected_list, 3);
  list* filtered_list = filter(list_, is_odd);
  cr_assert(eq(int, equal(filtered_list, expected_list), 1));
  free_list(filtered_list);
  free_list(expected_list);
  free_list(list_);
}

// Concatenating no lists returns an empty list.
Test(concat, none) {
  list* empty_list = make_list();
  list* concat_nothing = concat(NULL);
  cr_assert(eq(int, equal(concat_nothing, empty_list), 1));
  free_list(concat_nothing);
  free_list(empty_list);
}

// Concatenating lists combines the elements of the lists in the correct order.
Test(concat, correct_order) {
  list* list_1 = make_list();
  append(list_1, 1);
  append(list_1, 2);
  append(list_1, 3);
  list* list_2 = make_list();
  append(list_2, 4);
  append(list_2, 5);
  append(list_2, 6);
  list* concat_list = concat(list_1, list_2, NULL);
  free_list(list_1);
  free_list(list_2);
  list* expected_list = make_list();
  append(expected_list, 1);
  append(expected_list, 2);
  append(expected_list, 3);
  append(expected_list, 4);
  append(expected_list, 5);
  append(expected_list, 6);
  cr_assert(eq(int, equal(concat_list, expected_list), 1));
  free_list(concat_list);
  free_list(expected_list);
}

// The null pointer successfully terminates concatenation, even if there are
// other lists.
Test(concat, ignore_after_null_pointer) {
  list* list_1 = make_list();
  append(list_1, 1);
  append(list_1, 2);
  append(list_1, 3);
  list* list_2 = make_list();
  append(list_2, 4);
  append(list_2, 5);
  append(list_2, 6);
  list* list_3 = make_list();
  append(list_3, 7);
  append(list_3, 8);
  append(list_3, 9);
  list* concat_list = concat(list_1, list_2, NULL, list_3);
  free_list(list_1);
  free_list(list_2);
  free_list(list_3);
  list* expected_list = make_list();
  append(expected_list, 1);
  append(expected_list, 2);
  append(expected_list, 3);
  append(expected_list, 4);
  append(expected_list, 5);
  append(expected_list, 6);
  cr_assert(eq(int, equal(concat_list, expected_list), 1));
  free_list(concat_list);
  free_list(expected_list);
}

// NOLINTEND(*-magic-numbers)
