# Rubric for Assignment 1: Compilation and Memory

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

### 1. Worst-Of Compilation

For each of the four questions in `compilation.md`:

2: The change produces the error as described, and the error is in the correct
part of the compilation process.

1: The change produces the error as described, but not in the correct part of
the compilation process.

0: The change does not produce an error in the compilation process.

### 2. This Program Just `fgets` Me

For `shout` in `src/shout.c`:

2: The code passes all unit tests.

1: The code fails one or more unit tests due to a minor error.

0: The code fails one or more unit tests due to a major error.

### 3. Sorting Out Some Arrays

For each of `swap`, `sort_inplace`, and `sort_copy` in `src/array_sort.c`:

2: The code passes all unit tests.

1: The code fails one or more unit tests due to a minor error.

0: The code fails one or more unit tests due to a major error.

### Points Summary

**Correctness Score: XX/16**

## Style and Clean Code

### Documentation Comments

For each of `swap`, `sort_inplace` and `sort_copy` in `src/array_sort.h`:

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

**Total score: XX/35**
