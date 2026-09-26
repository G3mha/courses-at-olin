/**
 * Library implementation for shell utility functions.
 *
 * @author Steve Matsumoto
 * @copyright GNU GPLv3
 * @date 2023
 */

#include <stdio.h>
#include <stdlib.h>

#include "shell.h"
#include "string_array.h"

void shell_loop(void) {
  while (!feof(stdin)) {
    printf("%s", PROMPT);
    char* line = read_line();
    if (line == NULL) {
      puts("");
      free(line);
      continue;
    }
    string_array* tokens = tokenize_line(line);
    command* command_ = process_tokens(tokens);
    process_command(command_);
    free(line);
    free_string_array(tokens);
    free_command(command_);
  }
}

int main(void) {
  shell_loop();
  return EXIT_SUCCESS;
}
