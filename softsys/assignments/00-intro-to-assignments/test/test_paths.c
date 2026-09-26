#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/paths.h"

// Check that selecting the left path works.
Test(select_path, left_path, .init = cr_redirect_stdout) {
  select_path(1);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("You go left. You end up in downtown Needham.\n");
}

// Check that selecting the right path works.
Test(select_path, right_path, .init = cr_redirect_stdout) {
  select_path(2);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("You go right. You end up at the Wellesley dump.\n");
}

// Check that selecting the straight path works.
Test(select_path, straight_path, .init = cr_redirect_stdout) {
  select_path(3);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "You go straight. You end up in a strangely quiet Needham street.\n");
}

// Check that selecting zero results in the default message.
Test(select_path, zero_default, .init = cr_redirect_stdout) {
  select_path(0);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("Choices are hard. You go back to campus.\n");
}

// Check that selecting a negative number results in the default message.
Test(select_path, negative_default, .init = cr_redirect_stdout) {
  select_path(-1);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("Choices are hard. You go back to campus.\n");
}
