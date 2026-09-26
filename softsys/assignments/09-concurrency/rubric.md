# Rubric for Assignment 9: Threading

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

### 1. No Thread Left Behind

#### Scope of Changes

1: Only the implementation file (`weave.c`) was changed.

0: One or more files other than the above were changed.

#### Correctness

3: The implementation passes all unit tests.

2: The implementation does not pass all unit tests due to a minor error.

1: The implementation does not pass all unit tests due to a major error.

0: The implementation is missing or unchanged from its initial state.

#### Memory Management

2: The implementation does not leak any memory as reported by Valgrind.

1: The implementation leaks some memory as reported by Valgrind.

0: The implementation leaks all dynamically memory as reported by Valgrind

### Points Summary

**Correctness Score: XX/6**

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

**Total score: XX/16**
