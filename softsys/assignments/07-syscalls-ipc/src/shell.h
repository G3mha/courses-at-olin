/**
 * Library header for shell utility functions.
 *
 * @author Steve Matsumoto
 * @copyright GNU GPLv3
 * @date 2023
 */
#pragma once

#include <stdlib.h>

#include "string_array.h"

extern const size_t INITIAL_LINE_SIZE;
extern const size_t INITIAL_TOKENS_CAPACITY;
extern const char PROMPT[];

// A set of strings and string array that represents a command to be run.
typedef struct {
  /// The tokens of the command to run (essentially an argv).
  string_array* tokens;
  /// A path to the input file (which will be redirected to stdin).
  char* input_file;
  /// A path to the output file (which stdout will be redirected to).
  char* output_file;
} command;

/**
 * Make a new command instance whose tokens array has a given capacity.
 *
 * Create a new command on the heap and return a pointer to it. The caller is
 * responsible for cleaning up the memory allocated for the command.
 *
 * @param token_capacity The starting capacity of the tokens array.
 * @return The address of the new command.
 */
command* make_command(size_t token_capacity);

/**
 * Free the memory allocated for a command.
 *
 * Given a pointer to a command struct, free the dynamic memory allocated for
 * that struct. Attempting to free a pointer not to a command, freeing a command
 * that has already been free, or freeing an unallocated command* will result in
 * undefined behavior.
 *
 * @param command_ The pointer to the command to free.
 */
void free_command(command* command_);

/**
 * Read a line of input from the user, dynamically allocating memory as
 * necessary.
 *
 * Read a line from standard input until a newline or end of file is reached. If
 * a newline is provided, it is included in the line. If a line was read at all,
 * include a null terminator. In the event of an error while reading, return
 * NULL and free any memory allocated during the execution of the function. The
 * caller is responsible for cleaning up this function.
 *
 * @return A pointer to the line of input.
 */
char* read_line(void);

/**
 * Split a line of input into tokens.
 *
 * Given a line of null-terminated input, split a string by whitespace into
 * tokens. The original line is not changed, and new memory is dynamically
 * allocated for the array of strings. The caller is responsible for cleaning up
 * the memory allocated by this function.
 *
 * @param line A line of input.
 * @return A pointer to the array of strings.
 */
string_array* tokenize_line(const char* line);

/**
 * Process a tokenized line of input.
 *
 * Given an array of strings representing the tokens of an input line, process
 * these tokens into the following: (1) the tokens of the command, in order, (2)
 * the path of the file to be redirected to standard input, if any, and (3) the
 * path of the file to redirect standard output to, if any.
 *
 * Create a new command struct to represent these items and return this struct
 * to the user. Memory is dynamically allocated for this struct, so the caller
 * is responsible for cleaning up this command.
 *
 * @param tokens A pointer to the tokens array.
 * @return A pointer to the command struct representing a command to run.
 */
command* process_tokens(const string_array* tokens);

/**
 * Run a specific command.
 *
 * Given a pointer to a command, which includes the array of tokens in the
 * command, along with possible redirections for standard input and output, run
 * the given command. The current process image is replaced by the command, so
 * if successful, this function does not return.
 *
 * If standard input or output are redirected, their file descriptors are
 * overwritten by those for the input and output file, respectively. Those new
 * file descriptors are created, copied to 0 and 1, and then the new file
 * descriptors are closed.
 *
 * @param command_ A pointer to the command to run.
 */
void run(const command* command_);

/**
 * Process and run a command.
 *
 * Given a command, fork a process and run the command with the appropriate
 * redirections. If successful, the child process runs a command and does not
 * return. The parent process waits for the child to finish, and exits without
 * output (other than that of the child process).
 *
 * @param command_ A pointer to the command to run.
 */
void process_command(const command* command_);
