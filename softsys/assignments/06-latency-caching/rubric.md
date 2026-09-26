# Rubric for Assignment 6: Latency and caching

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

### 1. Transpose for the Camera

#### Scope of Changes

1: Only the implementation file (`src/transpose.c`) and README were changed.

0: One or more files other than the above were changed.

#### Cache Performance

Note that to get credit for this section, the `is_tranpose::test` unit test
**must** pass.

For the `transpose` function:

1 point for 100 fewer misses than the reference implementation, when run with
the provided unit tests. 1 additional point for each additional 50 fewer misses
thereafter (e.g., 150 fewer misses is 2 points, 200 fewer misses is 3 points, up
to 600 fewer misses, which is 11 points).

0: The function yields up to 99 fewer misses than the reference implementation,
or more misses.

#### Explanation

3: The explanation of the approach to optimizing cache performance in the README
is clearly explained and technically sound.

2: The explanation of the approach is slightly unclear, or contains minor
technical errors.

1: The explanation of the approach is significantly unclear, or contains major
technical errors.

0: The explanation is missing.

#### Extra Credit

1 point for every 500 fewer misses than the reference implementation, starting
at 1100 fewer misses (1100 fewer misses is 1 extra point).

### Points Summary

**Correctness Score: XX/14**

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

**Total score: XX/24**
