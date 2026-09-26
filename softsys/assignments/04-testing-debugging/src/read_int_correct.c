#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_int.h"

static void flush_input_line(void) {
  char null_buffer[BUFFER_SIZE];
  do {
    (void)fgets(null_buffer, sizeof(null_buffer), stdin);
  } while (strchr(null_buffer, '\n') == NULL);
}

int read_int(int* output) {
  char buffer[BUFFER_SIZE];
  (void)fgets(buffer, sizeof(buffer), stdin);
  if (strchr(buffer, '\n') == NULL) {
    // Clear the rest of the input line from stdin so it doesn't affect future
    // calls.
    flush_input_line();
    return 0;
  }
  *output = (int)strtol(buffer, NULL, DECIMAL_BASE);
  // The input can be at most three characters, so between -99 and 999
  // inclusive. Also, 0 is not allowed.
  // NOLINTNEXTLINE(*-magic-numbers)
  return *output != 0 && *output > -100 && *output < 1000;
}
