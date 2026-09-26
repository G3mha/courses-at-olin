#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/greet.h"

// Check that an empty string prints the greeting properly.
Test(greet, greet_empty, .init = cr_redirect_stdout) {
  const char* empty_string = "";
  greet(empty_string);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("Greetings, !\n");
}

// Check that a non-empty string prints the greeting properly.
Test(greet, greet_nonempty, .init = cr_redirect_stdout) {
  const char* nonempty_string = "Guido";
  greet(nonempty_string);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("Greetings, Guido!\n");
}
