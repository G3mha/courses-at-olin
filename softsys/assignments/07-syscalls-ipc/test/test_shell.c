#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/shell.h"
#include "../src/string_array.h"

// A new command should not have its input or output files set.
Test(make_command, null_io_file) {
  command* command_ = make_command(0);
  // Here and elsewhere in the file, use cr_expect instead of cr_assert so that
  // even if a test fails, dynamically allocated memory will be freed. Using
  // cr_assert aborts the test immediately, which would cause memory leaks.
  cr_expect(zero(ptr, command_->input_file));
  cr_expect(zero(ptr, command_->output_file));
  free_command(command_);
}

// A new command should have an empty tokens array with the given capacity.
Test(make_command, empty_tokens_array) {
  command* command_ = make_command(0);
  cr_expect(zero(sz, command_->tokens->size));
  cr_expect(zero(sz, command_->tokens->capacity));
  free_command(command_);
}

// Check that a line of input is read correctly from the user.
Test(read_line, input_line_read) {
  FILE* redirected_stdin = cr_get_redirected_stdin();
  char* ls_command = "ls -la /home/user\n";
  (void)fprintf(redirected_stdin, "%s", ls_command);
  (void)fclose(redirected_stdin);
  char* line = read_line();
  cr_expect(eq(str, line, ls_command));
  free(line);
}

// Check that the correct number of tokens is read in.
Test(tokenize_line, correct_size) {
  char* ls_command = "ls -la /home/user\n";
  string_array* tokens = tokenize_line(ls_command);
  cr_expect(eq(sz, tokens->size, 3));
  free_string_array(tokens);
}

// Check that the correct tokens are read in.
Test(tokenize_line, correct_tokens) {
  char* ls_command = "ls -la /home/user\n";
  string_array* tokens = tokenize_line(ls_command);
  cr_expect(eq(str, tokens->strings[0], "ls"));
  cr_expect(eq(str, tokens->strings[1], "-la"));
  cr_expect(eq(str, tokens->strings[2], "/home/user"));
  free_string_array(tokens);
}

// Check that processing a simple line with no redirections is done properly.
Test(process_tokens, no_redirection) {
  char* ls_command = "ls -la /home/user\n";
  string_array* tokens = tokenize_line(ls_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->tokens->strings[0], "ls"));
  cr_expect(eq(str, command_->tokens->strings[1], "-la"));
  cr_expect(eq(str, command_->tokens->strings[2], "/home/user"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that redirection with input and output files reads in the correct
// tokens.
Test(process_tokens, tokens_with_redirection) {
  char* cat_command = "cat <foo.txt >bar.txt\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->tokens->strings[0], "cat"));
  cr_expect(eq(sz, command_->tokens->size, 1));
  free_string_array(tokens);
  free_command(command_);
}

// Check that input redirection works at the beginning of a line.
Test(process_tokens, input_redirect_beginning) {
  char* cat_command = "<foo.txt cat -n\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->input_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that input redirection works at the middle of a line.
Test(process_tokens, input_redirect_middle) {
  char* cat_command = "cat <foo.txt -n\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->input_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that input redirection works at the end of a line.
Test(process_tokens, input_redirect_end) {
  char* cat_command = "cat -n <foo.txt\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->input_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that output redirection works at the beginning of a line.
Test(process_tokens, output_redirect_beginning) {
  char* cat_command = ">foo.txt cat -n\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->output_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that output redirection works at the middle of a line.
Test(process_tokens, output_redirect_middle) {
  char* cat_command = "cat >foo.txt -n\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->output_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// Check that output redirection works at the end of a line.
Test(process_tokens, output_redirect_end) {
  char* cat_command = "cat -n >foo.txt\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  cr_expect(eq(str, command_->output_file, "foo.txt"));
  free_string_array(tokens);
  free_command(command_);
}

// No tests for run, as it sets up and calls exec, and thus will never return if
// successful.

// Check that running a simple command with no I/O redirection causes the
// intended output.
Test(process_command, no_redirection, .init = cr_redirect_stdout) {
  char* cat_command = "echo Hello world!\n";
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  process_command(command_);
  cr_expect_stdout_eq_str("Hello world!\n");
  free_string_array(tokens);
  free_command(command_);
}

// Check that running a command works with an input file.
Test(process_command, input_redirection, .init = cr_redirect_stdout) {
  // Create a temporary filename at the path /tmp/ifileXXXXXX (X's filled in) to
  // read input from.
  char* input_file_path = tempnam("/tmp", "ifile");
  // Log the temporary filename so it can be inspected if needed.
  cr_log_info("Temporary input file: %s\n", input_file_path);
  // NOLINTNEXTLINE(android-cloexec-fopen)
  FILE* input_file = fopen(input_file_path, "w");
  (void)fprintf(input_file, "Hello world!\n");
  (void)fclose(input_file);

  // Construct the shell command with the previous temporary file name.
  char* command_prefix = "cat <";
  char* cat_command =
      malloc(strlen(command_prefix) + strlen(input_file_path) + 2);
  // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
  (void)sprintf(cat_command, "%s%s\n", command_prefix, input_file_path);

  // Check that running the command reads from the file correctly.
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  process_command(command_);
  cr_expect_stdout_eq_str("Hello world!\n");

  // Clean up.
  free(input_file_path);
  free(cat_command);
  free_string_array(tokens);
  free_command(command_);
}

// Check that running a command work with an output file.
Test(process_command, output_redirection, .init = cr_redirect_stdout) {
  // Create a temporary filename at the path /tmp/ofileXXXXXX (X's filled in) to
  // log the output to.
  char* output_file_path = tempnam("/tmp", "ofile");
  // Log the temporary filename so it can be inspected if needed.
  cr_log_info("Temporary output file: %s\n", output_file_path);

  // Construct the shell command with the previous temporary file name.
  char* command_prefix = "echo Hello world! >";
  char* cat_command =
      malloc(strlen(command_prefix) + strlen(output_file_path) + 2);
  // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
  (void)sprintf(cat_command, "%s%s\n", command_prefix, output_file_path);

  // Make sure the command produces no output on stdout.
  string_array* tokens = tokenize_line(cat_command);
  command* command_ = process_tokens(tokens);
  process_command(command_);
  // The command shouldn't print anything to stdout.
  cr_expect_stdout_eq_str("");

  // Check that the file contents equal what was written. (Note that echo adds a
  // newline.)
  // NOLINTNEXTLINE(android-cloexec-fopen)
  FILE* output_file = fopen(output_file_path, "r");
  char* output_line = NULL;
  size_t output_line_len = 0;
  (void)getline(&output_line, &output_line_len, output_file);
  cr_expect(eq(str, output_line, "Hello world!\n"));

  // Clean up.
  (void)fclose(output_file);
  free(output_line);
  free_command(command_);
  free_string_array(tokens);
  free(cat_command);
  free(output_file_path);
}
