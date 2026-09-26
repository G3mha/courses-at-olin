#include <stdio.h>   // printf, stderr
#include <stdlib.h>  // strtol, EXIT_SUCCESS, EXIT_FAILURE

int array_sum(const int num_array[], int num_array_len) {
  int sum = 0;
  for (int i = 0; i < num_array_len; ++i) {
    sum += num_array[i];
  }
  return sum;
}

int square(int num) {
  // pow() in math.h only handles floats, so we have to write our own here.
  return num * num;
}

void rewrite_array_value(int* num_addr, int new_value) {
  *num_addr = new_value;
}

int square_sum(int num_array[], int num_array_len) {
  int index = 0;
  int* current_position = num_array;
  while (index < num_array_len) {
    rewrite_array_value(++current_position, square(num_array[++index]));
  }
  return array_sum(num_array, num_array_len);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    (void)fprintf(stderr, "Must provide exactly one argument\n");
    return EXIT_FAILURE;
  }
  // NOLINTNEXTLINE(*-magic-numbers)
  int sum_len = (int)strtol(argv[1], NULL, 10);
  // First 10 Fibonacci numbers.
  // NOLINTBEGIN(*-magic-numbers)
  int FIBONACCI_NUMS[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
  // NOLINTEND(*-magic-numbers)
  for (int i = 1; i <= sum_len; ++i) {
    printf("The sum of the squares of the first %d Fibonacci numbers is %d\n",
           i, square_sum(FIBONACCI_NUMS, i));
  }
  // EXIT_SUCCESS is a macro for 0.
  return EXIT_SUCCESS;
}
