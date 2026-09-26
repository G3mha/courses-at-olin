#pragma once

#include <stddef.h>
/**
 * Take two int pointers and swap values.
 *
 * @param left_ptr - pointer to the left int.
 * @param right_ptr - pointer to the right int.
 */
void swap(int* left_ptr, int* right_ptr);

/**
 * Sort an array of integers in place.
 * 
 * @param numbers - array of integers to sort.
 * @param array_size - number of elements in the array.
 */
void sort_inplace(int numbers[], size_t array_size);

/**
 * Create sorted copy of an array of integers.
 * 
 * @param numbers - array of integers to sort.
 * @param sorted - array to store the sorted integers.
 * @param array_size - number of elements in the array.
 */
void sort_copy(const int numbers[], int sorted[], size_t array_size);
