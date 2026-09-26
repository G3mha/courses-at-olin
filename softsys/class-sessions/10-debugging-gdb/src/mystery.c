#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t compute_R(uint32_t k)
{
  uint64_t k64 = (uint64_t)k;
  return (uint32_t)(((UINT64_C(1) << 32) + (k64 - 1)) / k64);
}

uint32_t process_R(uint32_t n, uint32_t R)
{
  return (uint32_t)(((uint64_t)n * (uint64_t)R) >> 32);
}

uint32_t f(uint32_t n, uint32_t k) {
  uint32_t R = compute_R(k);
  return process_R(n, R);
}

int main(int argc, char* argv[]) {
  uint32_t n = (uint32_t)strtol(argv[1], NULL, 10);
  uint32_t k = (uint32_t)strtol(argv[2], NULL, 10);
  uint32_t d = f(n, k);
  printf("f(%u, %u) = %u\n", n, k, d);
  return EXIT_SUCCESS;
}
