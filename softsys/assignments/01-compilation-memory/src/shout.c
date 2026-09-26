#include "shout.h"

#include <ctype.h>
#include <stdio.h>

void shout(void) {
  char buffer[BUFFER_SIZE + 1];
  if (fgets(buffer, BUFFER_SIZE + 1, stdin) != NULL) {
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (islower(buffer[i])) {
        buffer[i] = toupper(buffer[i]);
      }
      if (buffer[i] == '\n') {
        buffer[i] = '\0';
        break;
      }
    }
    printf("%s\n", buffer);
  }
}
