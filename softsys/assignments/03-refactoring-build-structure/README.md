# Assignment 3: Refactoring, Build Systems, and Project Structure

In this assignment, you will get the chance to learn about build systems, header
files, and project structure through the process of refactoring. You do not have
to read or write much code for this assignment, though

## 0. Setup

### 0.1. Sync and Branch Your Repo

Make sure that you are at the latest change in your repo by running the
following commands:

```
$ git switch main
$ git pull
$ git pull upstream main
$ git push
```

If you run into issues performing the above operations, ask for help on Discord.

Once you have done this, create a new branch for this assignment:

```
$ git switch -c assignment-03
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. Refac-tic-tac-toe

In this problem, we have provided you with a working, but rather poorly
organized implementation of a simple text-based game of tic-tac-toe. If you want
to try it for yourself, you can compile and run the `src/run_tic_tac_toe`
program.

Your task is to refactor this project. Specifically, you need to do the
following:

- Split the source `tic_tac_toe.c` and `tic_tac_toe.h` into **at least three**
  pairs of files, where each pair of files is defined as a `.c` file and its
  corresponding `.h` file (e.g., `foo.c` and `foo.h`). These files should be
  logically organized so what they contain makes sense in the overall context of
  the project.
- Split the test file `test_tic_tac_toe.c` into **at least three** test files,
  each of which tests an appropriate part of the code. Like the code files,
  these should be logically organized in the overall context of the project. A
  straightforward way to arrange these (in some cases) is to follow the
  structure of the code.
- Edit the `CMakeLists.txt` files in `src/` and `test/` to build correctly.

Your refactoring should not change any behavior of the code; in other words, all
of the unit tests should still pass after your changes. In addition, you should
not `#include` (in C files) or link (in `CMakeLists.txt` files) any unnecessary
files/libraries.

Below, you will find some information that may be helpful as you do your
refactoring.

### Global Constants and `enum`s

Defining global constants in C can be a bit tricky, which explains why the
constants in the starter file are defined the way they are.

It is recommended that you define integer constants in an `enum`, as seen in the
initial state of `tic_tac_toe.h`. We won't get too much into details here, but
an `enum` essentially lets you define variables that correspond to specific
unique constants. If you split these constants across multiple files, you can
define them in separate enums, one in each file. These should stay in header
files.

In C17, `enum`s can only refer to `int`s (though this will change in future
standards). Because of this, other types (like `char`s) must be defined as
`const` values. You may notice that `tic_tac_toe.h` declares these as
`extern const`, which essentially means that the definition (value) of each of
these constants is in another file - the corresponding `.c` file. This is done
because even with include guards, there are ways for constant values in header
files to be defined more than once in linking, causing issues. The solution is
to define the values in the `.c` file instead, and letting the linker (rather
than the preprocessor) handle the value.

In general, if you mess something up with constnts, you will encounter a problem
during the build process, or Clang-tidy will warn you.

### Static Functions

In `tic_tac_toe.c`, you may notice some functions marked as `static`, like
`static void flush_input_line(void)`. A static function is not visible outside
of the file, which essentially makes it usable only within that file (not quite
true, but close enough for our purposes). This makes it ideal for use as a
helper function. In this project, we use static functions for this purpose, so
any function that calls a static function will need to be in the same file. This
may affect how you organize your code.

### CMake Files

Your `CMakeLists.txt` files define a series of targets, which are executables or
libraries. Remember that the rule of thumb is that if a `.c` file has a `main`
function, then it should be treated as an executable, and a library otherwise.

If you create a new file in `test/CMakeLists.txt`, be aware that in addition to
defining a target and linking the appropriate libraries, you also need to add an
`add_test` command, which will tell CMake to include the tests in the overall
test suite. This in turn will let you run the tests within VS Code's interface
or on the command line by running `make test` or `ctest` in the `build/`
directory. For how to do this, see the starter `CMakeLists.txt` file in `test/`.

In general, you should feel free to use `CMakeLists.txt` files from this and
past assignments to get a snese of how to organize and write your
`CMakeLists.txt` file for this assignment.

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `src` and the `test` directory. Be sure to write a reasonably
clear commit message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
