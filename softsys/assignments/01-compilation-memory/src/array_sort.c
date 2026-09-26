#include "array_sort.h"

#include <stdlib.h>

void swap(int* left_ptr, int* right_ptr) {
  int temp = *left_ptr;
  *left_ptr = *right_ptr;
  *right_ptr = temp;
}

void sort_inplace(int numbers[], size_t array_size) {
  for (size_t i = 0; i < array_size-1; i++) {
    for (size_t j = i + 1; j < array_size; j++) {
      if (numbers[j] < numbers[i]) {
        swap(&numbers[i], &numbers[j]);
      }
    }
  }
}

void sort_copy(const int numbers[], int sorted[], size_t array_size) {
  for (size_t i = 0; i < array_size; i++) {
    sorted[i] = numbers[i];
  }
  sort_inplace(sorted, array_size);
}
