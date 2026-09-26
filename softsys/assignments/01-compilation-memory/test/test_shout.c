#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/shout.h"

/**
 * Send a line of input to a redirected stdin stream.
 * @param input The input to send, without the terminating newline.
 */
void send_stdin(const char* input) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "%s\n", input);
  (void)fclose(stdin_file);
}

/**
 * Check that the output on stdout is an expected string.
 * @param output The expected output, including a possible terminating newline.
 */
void assert_stdout(const char* output) {
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(output);
}

// An empty string remains as is.
Test(shout, empty_string_unchanged, .init = cr_redirect_stdout) {
  send_stdin("");
  shout();
  assert_stdout("\n");
}

// A string of all lowercase letters should be capitalized.
Test(shout, lowercase_converted, .init = cr_redirect_stdout) {
  send_stdin("hello");
  shout();
  assert_stdout("HELLO\n");
}

// Anything after the first newline is ignored.
Test(shout, additional_input_lines_ignored, .init = cr_redirect_stdout) {
  send_stdin("hello\nthere");
  shout();
  assert_stdout("HELLO\n");
}

// Non-lowercase characters remain as is.
Test(shout, non_lowercase_letters_preserved, .init = cr_redirect_stdout) {
  send_stdin("I am totally not a robot.");
  shout();
  assert_stdout("I AM TOTALLY NOT A ROBOT.\n");
}

// Inputting a string that is exactly the maximum length will still work.
Test(shout, max_buffer_size_works, .init = cr_redirect_stdout) {
  // BUFFER_SIZE (defined in shout.h) must be 32 for this test to work, so make
  // sure that is the case first.
  cr_assert(eq(int, BUFFER_SIZE, 32));

  send_stdin("This is exactly 32 characters!!");
  shout();
  assert_stdout("THIS IS EXACTLY 32 CHARACTERS!!\n");
}

// Inputting a string that is too long will result in it getting cut off.
Test(shout, excessive_input_truncated, .init = cr_redirect_stdout) {
  // BUFFER_SIZE (defined in shout.h) must be 32 for this test to work, so make
  // sure that is the case first.
  cr_assert(eq(int, BUFFER_SIZE, 32));

  send_stdin("This input is way too long. What will happen here?");
  shout();
  assert_stdout("THIS INPUT IS WAY TOO LONG. WHAT\n");
}
