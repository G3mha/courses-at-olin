#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dollarize(char* string) {
    string[0] = "$";
}

void copy_name(char* src, char* dst) {
    int current_index = 0;
    while (src[current_index] != '\0') {
        dst[current_index] = src[current_index];
        ++current_index;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Must provide exactly one command-line argument\n");
        return EXIT_FAILURE;
    }
    char buffer[20];
    copy_name(argv[1], buffer);
    return EXIT_SUCCESS;
}
