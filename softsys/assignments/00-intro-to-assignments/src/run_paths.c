#include <stdio.h>

#include "paths.h"

int main(void) {
  int choice;
  printf("Enter a path (1-3): ");
  scanf("%d", &choice);
  select_path(choice);
  return 0;
}
