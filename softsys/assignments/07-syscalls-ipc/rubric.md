# Rubric for Assignment 7: System Calls and Interprocess Communication

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

### 1. Don't Get Crabby

#### Scope of Changes

1: Only the implementation file (`src/shell.c`) was changed.

0: One or more files other than the above were changed.

#### Unit Tests

For each of the functions `process_tokens` and `process_command`:

3: The function passes all unit tests.

2: The function passes more unit tests than the starting implementation, but not
all, due to a minor (easily fixable) error.

1: The function passes more unit tests than the starting implementation, but not
all, due to a major error

0: The function passes the same or fewer unit tests than the starting
implementation.

#### Error Handling

For each of the following function calls:

- `malloc`
- `fork`
- `open`
- `close`
- `dup2`
- `waitpid`
- `exec` (and its variants)

2: All instances of these calls are checked for errors, and the errors handled
appropriately (e.g., printing a message and exiting with a nonzero status).

1: At least one instance of these calls is checked for errors, and the errors
are handled appropriately, but this does not apply all instances.

0: No instance of the call is checked for errors, or no instances of the calls
are used.

### Points Summary

**Correctness Score: XX/19**

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

**Total score: XX/29**
