#include <assert.h>
#include <stdlib.h>

#include "mean.h"

float mean(const int array[], size_t array_len) {
  assert(array_len > 0);
  int sum = 0;
  for (size_t i = 0; i < array_len; ++i) {
    sum += array[i];
  }
  return (float)sum / (float)array_len;
}
