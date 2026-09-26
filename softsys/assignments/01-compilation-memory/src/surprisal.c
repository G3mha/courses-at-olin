#include <math.h>
#include <stdio.h>

double surprisal(double prob) {
  if (prob == 0) {
    return -1.0;
  }
  return -log2(prob);
}

int main(void) {
  const int MAX_PERCENTAGE = 100;
  const double PERCENT_PROB = 0.01;
  for (int i = 1; i < MAX_PERCENTAGE; ++i) {
    double prob = i * PERCENT_PROB;
    printf("The surprisal of an event with probability %.2f is %.3f bits.\n",
           prob, surprisal(prob));
  }
  return 0;
}
