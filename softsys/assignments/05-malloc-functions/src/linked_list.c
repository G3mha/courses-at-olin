#include "linked_list.h"

#include <stdarg.h>
#include <stdlib.h>

node* make_node(int val) {
  node* new_node = malloc(sizeof(node));
  new_node->val = val;
  new_node->next = NULL;
  return new_node;
}

void free_node(node* node_) { free(node_); }

list* make_list(void) {
  // Replace this with your implementation.
  return NULL;
}

list* copy(const list* list_) {
  // Replace this with your implementation.
  return NULL;
}

void free_list(list* list_) {
  // Replace this with your implementation.
}

int get(const list* list_, size_t index, int* status) {
  // Replace this with your implementation.
  return 0;
}

int equal(const list* lhs, const list* rhs) {
  // Replace this with your implementation.
  return 0;
}

void reverse(list* list_) {
  // Replace this with your implementation.
}

void append(list* list_, int val) {
  // Replace this with your implementation.
}

list* filter(const list* list_, int (*cond)(int)) {
  // Replace this with your implementation.
  return NULL;
}

list* concat(const list* list_, ...) {
  // Replace this with your implementation.
  return NULL;
}
