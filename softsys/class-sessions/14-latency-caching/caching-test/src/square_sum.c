#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // Check and parse command-line arguments.
  if (argc != 3) {
    return 1;
  }
  size_t array_dim = (size_t)strtol(argv[1], NULL, 10);
  int version = (int)strtol(argv[2], NULL, 10);

  // Create and fill the array.
  int* array = malloc(array_dim * array_dim * sizeof(int));
  if (!array) {
    return 1;
  }
  for (size_t i = 0; i < array_dim; ++i) {
    for (size_t j = 0; j < array_dim; ++j) {
      array[i * array_dim + j] = 1;
    }
  }

  // Add the elements of the array and print the sum.
  int sum = 0;
  if (version) {
    for (size_t i = 0; i < array_dim; ++i) {
      for (size_t j = 0; j < array_dim; ++j) {
        sum += array[i * array_dim + j];
      }
    }
  } else {
    for (size_t j = 0; j < array_dim; ++j) {
      for (size_t i = 0; i < array_dim; ++i) {
        sum += array[i * array_dim + j];
      }
    }
  }
  printf("%d\n", sum);

  // Clean up and exit.
  free(array);
  return 0;
}
