/**
 * Linked list library.
 */
#pragma once

#include <stdlib.h>

typedef struct node {
  int val;
  struct node* next;
} node;

typedef struct {
  node* head;
  size_t len;
} list;

/**
 * Make a new node holding a given value.
 *
 * Given an integer value, create a new node on the heap holding that value and
 * return a pointer to that node. The caller of this function is considered the
 * owner of the new node and is responsible for cleaning it up when done with
 * it.
 *
 * @param val The value for the new node to hold.
 * @return A pointer to the newly created node.
 */
node* make_node(int val);

/**
 * Free a node's memory.
 *
 * Given a pointer to the node that was allocated on the heap, free the memory
 * taken up by that node. Generally, this function should only be called in
 * functions that originally allocated the node with make_node, or as part of
 * another free_* function whose corresponding make_* function and/or other
 * functions allocate nodes.
 *
 * If a node not allocated on the heap is attempted to be freed, the result is
 * undefined. Attempting to free a non-node, attempting to free a node that has
 * already been freed, and accessing a node after freeing will all result in
 * undefined behavior.
 *
 * @param node_ A pointer to the node to free.
 */
void free_node(node* node_);

/**
 * Create a new empty list.
 *
 * Create a new list that is empty (that is, it contains no integers and has a
 * size of zero). The memory for the new list is allocated on the heap.
 *
 * @return A pointer to the newly created list.
 */
list* make_list(void);

/**
 * Create a copy of a list.
 *
 * Given a list, create an identical copy of the list in value, allocating any
 * necessary memory for the copy on the heap. The copy is a deep copy, meaning
 * that new memory for the list and its nodes are allocated on the heap.
 *
 * @param list_ The list whose values should be copied.
 * @return A pointer to the newly created copy of list_.
 */
list* copy(const list* list_);

/**
 * Free a list's memory.
 *
 * Given a pointer to a list that was allocated on the heap, free the memory
 * taken up by that list. Any nodes contained in the list will be freed, as will
 * the list itself. Undefined behavior results if the passed pointer does not
 * point to a list allocated on the heap or has already been freed. Attempting
 * to access the list after it has been freed also results in undefined
 * behavior.
 *
 * @param list_ A pointer to the list to free.
 */
void free_list(list* list_);

/**
 * Get a value from the list by index.
 *
 * Given a list and index, return the value at that index in the list. The index
 * starts from zero, so the value at the head of the list is at index 0. If the
 * index is invalid (i.e., past the last index in the list), return 0. If a
 * non-null status pointer is passed, also write the success of the function
 * into the memory location at that pointer address (1 for success and 0 for
 * failure).
 *
 * If the pointer to the list or status is invalid (e.g., null pointer), the
 * behavior of this function is undefined.
 *
 * @param list_ A pointer to the list to get a value from.
 * @param index The index in the list to get the value from.
 * @param status A pointer to an integer to hold the success/failure status.
 * @return The value at index in list_, or 0 if failed.
 */
int get(const list* list_, size_t index, int* status);

/**
 * Check whether the contents of two lists are equal.
 *
 * Given two lists, check whether they are equal (i.e., their lengths are the
 * same and they contain the same values in the same order). The lists can point
 * to the same location, in which case they will be equal by definition, but
 * only the values (not the memory locations of the lists/nodes) are compared.
 *
 * @param lhs A pointer to one of the lists to compare.
 * @param rhs A pointer to the other list to compare.
 * @return 1 if the lists are equal in value and 0 otherwise.
 */
int equal(const list* lhs, const list* rhs);

/**
 * Reverse a list in place.
 *
 * Given a list, reverse its elements in place. The list should then contain the
 * same elements in reverse order. Any dynamically allocated memory owned by the
 * list may be freed as part of the implementation of this function.
 *
 * @param list_ A pointer to the list to reverse.
 */
void reverse(list* list_);

/**
 * Append a value to a list.
 *
 * Given a list and a value, add that value to the end of the list. This
 * function modified the list in place (i.e., it does not create a new copy of
 * the list to append to).
 *
 * @param list_ A pointer to the list to append to.
 * @param val The value to append.
 */
void append(list* list_, int val);

/**
 * Filter a list based on some condition.
 *
 * Given a list and a function, create a filtered version of the list containing
 * only the integers for which the function produces nonzero output. The
 * original list is unchanged, creating a new list in its place. The caller is
 * responsible for freeing the new filtered list. The filter function should
 * take an integer (the values held in the list) and return a nonzero value for
 * any integer to be kept in the list and 0 otherwise.
 *
 * @param list_ A pointer to the list to filter.
 * @param cond A function used to filter the list.
 * @return A pointer to the filtered list.
 */
list* filter(const list* list_, int (*cond)(int));

/**
 * Concatenate a number of lists together.
 *
 * Given some number of lists, concatenate them into a single, larger list. The
 * concatenated list is a new list dynamically allocated on the heap and
 * contains the contents of each passed list in order. To terminate the set of
 * lists, the final pointer passed to the function must be a null pointer.
 *
 * @param list_ A pointer to a list to concatenate (optionally followed by more
 * lists).
 * @return A pointer to a list containing the concatenation of all of the lists.
 */
list* concat(const list* list_, ...);
