#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // Check and parse command-line arguments.
  if (argc != 3) {
    return 1;
  }
  size_t array_len = (size_t)strtol(argv[1], NULL, 10);
  size_t skip_size = (size_t)strtol(argv[2], NULL, 10);

  // Create and fill the array.
  int* numbers = calloc(array_len, sizeof(int));
  if (!numbers) {
    return 1;
  }
  for (size_t i = 0; i < array_len; ++i) {
    numbers[i] = 1;
  }

  // Add up a subset of the array and print the sum.
  int sum = 0;
  for (size_t i = 0; i < array_len; i += skip_size) {
    sum += numbers[i];
  }
  printf("%d\n", sum);

  // Clean up and exit.
  free(numbers);
  return 0;
}
