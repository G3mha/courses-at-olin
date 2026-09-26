/**
 * Library implementation for shell utility functions.
 *
 * @author Steve Matsumoto
 * @copyright GNU GPLv3
 * @date 2023
 */

// The getline() function is provided by a set of extensions to the C library
// (ISO/IEC TR 24731-2:2010), as well as by the POSIX library. Use the
// appropriate version depending on what libraries the system has.
#ifdef __STDC_ALLOC_LIB__
// This definition must appear *before* including stdio.h.
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "shell.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// On the author's system, 95.3% of commands run over the past ~18 months are 64
// charaters or fewer (including a terminating null character). This initial
// line size minimizes the need for getline to reallocate a line buffer when
// reading a line of input from the user.
const size_t INITIAL_LINE_SIZE = 64;

// On the author's system, 96.6% of commands run over the past ~18 months have 8
// tokens or fewer (including a terminating null pointer to indicate the end of
// a token array). This initial capacity minimizes the need to reallocate the
// token buffer when processing a line of input from the user.
const size_t INITIAL_TOKENS_CAPACITY = 8;

const char PROMPT[] = "> ";

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static pthread_mutex_t exit_lock = PTHREAD_MUTEX_INITIALIZER;

static void error_and_exit(const char* error_message) {
  perror(error_message);
  pthread_mutex_lock(&exit_lock);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(1);
}

command* make_command(size_t token_capacity) {
  command* command_ = malloc(sizeof(command));
  command_->tokens = make_string_array(token_capacity);
  command_->input_file = NULL;
  command_->output_file = NULL;
  return command_;
}

void free_command(command* command_) {
  free_string_array(command_->tokens);
  free(command_->input_file);
  free(command_->output_file);
  free(command_);
}

char* read_line(void) {
  char* line = malloc(INITIAL_LINE_SIZE * sizeof(char));
  size_t line_size = INITIAL_LINE_SIZE;
  ssize_t getline_return = getline(&line, &line_size, stdin);
  if (getline_return == -1) {
    free(line);
    return NULL;
  }
  return line;
}

string_array* tokenize_line(const char* line) {
  string_array* tokens = make_string_array(INITIAL_TOKENS_CAPACITY);
  const char* token_start = line;
  size_t token_size = 0;
  for (const char* current_pos = line; *current_pos != '\0'; ++current_pos) {
    if (isspace((int)*current_pos)) {
      // If we are switching from non-whitespace to whitespace, we've reached
      // the end of a token, so add what we currently have.
      if (token_size) {
        add_string(tokens, token_start, token_size);
        token_size = 0;
      }
    } else {
      // If we are switching from whitespace to non-whitespace, we've reached
      // the start of a token, so move the token start position.
      if (token_size == 0) {
        token_start = current_pos;
      }
      ++token_size;
    }
  }
  return tokens;
}

command* process_tokens(const string_array* tokens) {
  // Replace this with your implementation.
  return NULL;
}

void run(const command* command_) {
  // Replace this with your implementation.
}

void process_command(const command* command_) {
  // Replace this with your implementation.
}
