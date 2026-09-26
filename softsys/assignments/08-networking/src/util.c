#include "util.h"

#include <stdint.h>  // uint16_t
#include <stdio.h>   // perror
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <unistd.h>  // close

const uint16_t PORT = 4242;

void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

int open_tcp_socket(void) {
  // Replace this with your implementation.
}

void close_tcp_socket(int socket_) {
  // Replace this with your implementation.
}

struct sockaddr_in socket_address(in_addr_t addr, in_port_t port) {
  // Replace this with your implementation.
  struct sockaddr_in foo;
  return foo;
}
