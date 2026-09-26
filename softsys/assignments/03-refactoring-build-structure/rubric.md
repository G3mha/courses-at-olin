# Rubric for Assignment 3: Refactoring, Build Systems, and Project Structure

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

### 1. Refac-tic-tac-toe

#### C File Split

2: `tic_tac_toe.c` and `tic_tac_toe.h` are split into at least three pairs of
files (each pair being a `.c` and its corresponding `.h` file).

1: `tic_tac_toe.c` and `tic_tac_toe.h` are split into two pairs files (each pair
being a `.c` and its corresponding `.h` file).

0: `tic_tac_toe.c` and `tic_tac_toe.h` are unchanged, or were only
renamed/reorganized within the files.

#### C File Organization

For each of the three pairs of files (or, if split into more pairs, the three
highest scoring pairs) one point for each of the following:

- The contents of the pair of files make logical sense.
- The files does not contain unnecessary `#include` statements.

This section is 6 points total.

#### Test File Split

2: `test_tic_tac_toe.c` is split into at least three test files.

1: `test_tic_tac_toe.c` is split into two test files.

0: `test_tic_tac_toe.c` is left as one file.

#### Test File Organization

For each of the three files (or, if split into more files, the three highest
scoring files) one point for each of the following:

- The contents of the file makes logical sense.
- The file does not contain unnecessary `#include` statements.

This section is 6 points total.

#### CMake Files

The `CMakeLists.txt` file in `src/` should define at least four targets, and the
one in `test/` should define at least three targets. For each of the 7 targets
(or the highest-scoring 4/3 targets in each file), one point for each of the
following:

- The target defined for the file (executable or library) is correct.
- The target includes only the necessary files as its source.
- The target is linked or otherwise set up (in the case of tests) correctly, and
  does not link unnecessary libraries.

This section is 21 points total.

#### Unit Tests

2: The code passes all included unit tests.

1: The code passes at least half, but not all, included unit tests.

0: The code passes fewer than half of the included unit tests.

### Points Summary

**Correctness Score: XX/39**

## Style and Clean Code

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

**Style and Clean Code Score: XX/6**

## Summary

Add up the points in the three totals here.

**Total score: XX/49**
