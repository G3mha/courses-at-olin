#include "paths.h"

#include <stdio.h>

void select_path(int selection) {
  switch (selection) {
  case 1:
    printf("You go left. You end up in downtown Needham.\n");
    break;
  case 2:
    printf("You go right. You end up at the Wellesley dump.\n");
    break;
  case 3:
    printf("You go straight. You end up in a strangely quiet Needham street.\n");
    break;
  default:
    printf("Choices are hard. You go back to campus.\n");
    break;
  }
}
