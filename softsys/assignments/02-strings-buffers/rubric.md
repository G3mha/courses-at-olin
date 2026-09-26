# Rubric for Assignment 2: Strings and Buffers

## Submission

### Canvas

1: The link submitted on Canvas is for the pull request containing the
assignment submission.

0: The link submitted on Canvas is not for the pull request containing the
assignment submission.

### Git Branch

1: The branch includes only changes for this assignment.

0: The branch includes commits or changes outside this assignment.

### Git Commit Message

1: All commit messages for the branch are reasonably clear.

0: One or more commit messages for the branch are reasonably clear.

### GitHub Pull Request

1: The pull request is made to the `main` branch of the student's fork of the
course repository.

0: The pull request is made to a branch other than `main` or to a repo that is
not the student's fork of the course repository.

### Points Summary

**Submission Score: XX/4**

## Correctness

### 1. `string` Along

For each of the four functions (`startswith`, `endswith`, `count`, and `strip`):

3: The code passes all unit tests.

2: The code fails one or more unit tests due to a minor error (e.g., off by one
error, forgot to initialize pointer).

1: The code fails one or more unit tests due to a major error (e.g., )

0: The code was not changed from its initial state.

#### Extra Credit

If the extra credit problem was completed, use the same rubric as above.

### Points Summary

**Correctness Score: XX/12**

(Note that a maximum of 15 points is possible here due to the extra credit.)

## Style and Clean Code

### Documentation Comments

For each of `startswith`, `endswith` and `count` in `src/string_utils.h`:

3: The documentation comment for the function describes (1) what the function
does in sufficient detail, (2) the parameter type(s) of the function, if
applicable, and (3) the return types and values of the function, where
applicable.

2: The documentation comment for the function is missing one of the above.

1: The documentation comment for the function is missing two of the above.

0: The documentation comment for the function is missing entirely.

### Clang-Format

2: Clang-Format produces no warnings when run on the changed files.

1: Clang-Format produces a few minor warnings when run on the changed files.

0: Clang-Format produces many warnings when run on the changed files.

### Clang-Tidy

2: Clang-Tidy produces no warnings when building with make.

1: Clang-Tidy produces a few minor warnings when building with make.

0: Clang-Tidy produces many warnings when building with make.

### Compiler Warnings

2: The compiler produces no warnings when building with make.

1: The compiler produces a few minor warnings when building with make.

0: The compiler produces many warnings when building with make.

### Points

**Style and Clean Code Score: XX/15**

## Summary

Add up the points in the three totals here.

**Total score: XX/31**
