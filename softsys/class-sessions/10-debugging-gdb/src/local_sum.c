#include <stdio.h>

int* sum(int numbers[], size_t numbers_len) {
    int s = 0;
    for (size_t i = 0; i < numbers_len; ++i) {
        s += numbers[i];
    }
    return &s;
}

void print_sum(int* array, size_t array_len) {
    int result = sum(array, array_len);
    int first = array[0];
    int last = array[array_len - 1];
    printf("The sum of the numbers %d to %d is %d\n", first, last, result);
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t numbers_len = 5;
    int* blank = NULL;
    size_t blank_len = 0;
    print_sum(numbers, numbers_len);
    print_sum(blank, blank_len);
    return 0;
}
