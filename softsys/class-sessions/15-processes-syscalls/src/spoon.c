#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  if (execlp("echo", "echo", "My spoon", NULL) == -1) {
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    (void)fprintf(stderr, "exec error: %s\n", strerror(errno));
  }
  if (execlp("echo", "echo", "is too big", NULL) == -1) {
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    (void)fprintf(stderr, "exec error: %s\n", strerror(errno));
  }
  return 0;
}
