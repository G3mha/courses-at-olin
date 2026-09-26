# Assignment 4: Testing

In this assignment, you will get the chance to write a few unit tests in the
[Criterion testing framework](https://github.com/Snaipe/Criterion).

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
$ git switch -c assignment-04
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

### 0.3. Install GDB (Linux, Intel Macs)

For this assignment, you'll need GDB. You can install that on Linux with

```
sudo apt install gdb
```

For Intel Macs, (anything that isn't an M1/M2/M3), you can do this through
[Homebrew](https://brew.sh) with

```
brew install gdb
```

It's also recommended (but not required) that you install GEF, a GDB extension
that simplifies a lot of the tedious work. The
[GEF GitHub page](https://github.com/hugsy/gef) has installation instructions.

### 0.4. Install Docker and Dev Containers (ARM Macs)

If you're on an ARM Mac (e.g., M1/M2 MacBook), you'll need to install Docker to
complete part of this assignment. Specifically, you'll need to install
[Docker Desktop](https://www.docker.com/products/docker-desktop/). We recommend
doing this through [Homebrew](https://brew.sh/):

```
brew install --cask docker
```

You'll also need the
[Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
extension for VS Code. Install the extension from the marketplace, either
through the link above or by manually searching for "Dev Containers".

## 1. Tests, Suite Tests

There are three functions to test in this problem:

- `mean`, which calculates the mean of an array of integers.
- `print_int`, which prints an integer to standard output.
- `read_int`, which reads in an integer between -99 and 999 (inclusive) from the
  user.

Each function has a correct implementation and an incorrect implementation - in
`src/`, you should see a function ending in `_correct.c` and `_incorrect.c`,
respectively. You should read these files and the `.h` files to get a sense of
what the functions expect to take and how the incorrect implementation might
fail.

Your job is to write unit tests to check these functions. Your goal is to write
tests where the correct implementations pass, but the incorrect implementations
can fail. In the `test/` directory, you will find three test files:
`test_mean.c`, `test_print_int.c`, and `test_read_int.c`. Fill in each of these
files with **at least three substantially different tests**, at least one of
which causes the incorrect implementation to fail and at least one of which the
incorrect implementation will still pass. (Here, "substantially different" means
checking a reasonably distinct "conceptual fact" about the code's behavior, as
explained below.)

**Please document your tests.** Above each test, write a short comment
explaining what behavior you are testing for. This should be about behavior and
not the test case; for example, if you are testing that the mean of the int
array `{42}` is `42.0`, your comment should say

```
// Check that the mean of an array with one element is that element.
```

instead of

```
// Check that the mean of {42} is 42.0.
```

In other words, your test should be checking for some conceptual fact about the
code's behavior (the mean of an array of one element).

You should not change any of the `CMakeLists.txt` files or any files in `src/`.
Also, the appropriate libraries have already been included for you in each of
the test files, so you should not need to change the `#include`s in those file
unless you need something else from the C standard library. (Our gentle hint is
that you probably don't need to include any other files, though.)

For `test_print_int.c` and `test_read_int.c`, you may find it helpful to read
the
[stream redirect sample for Criterion](https://github.com/Snaipe/Criterion/blob/bleeding/samples/redirect.c).
Note that on systems we have tested, you will sometimes encounter a crash when
writing tests as shown in this sample. In this case, running `fclose(stream)`
for the appropriate `stream` (e.g., `stdin`) after you are done using it will do
the trick.

For more subtle debugging purposes, we have also included a file called
`print_info.c` that you can use to print out some useful information about
certain types on your system. It is unlikely that you will run into issues, but
in case you do, the output of this program may be helpful.

## 2. Space to Roam (and Find Some Bugs)

It has been said by some that students graduating from Olin College are weak in
their fundamentals, a fact that has apparently emerged in conversation with an
indeterminate number of alumni and employers and for which no further details
can be provided. Thus, in this problem, we're going to return to the ultimate
fundamentals: C programming and arithmetic. With the help of GDB, you'll get the
chance to find these bugs and launch them out into the void of space with your
developing C skills. It's debugging practice at its finest.

Now that our mild satire and completely unnecessary problem setup is out of the
way, let's get into your actual task for this problem.

The file `src/add_nums.c` is intended to compute sums of the squares of the
first _n_ [Fibonacci numbers](https://en.wikipedia.org/wiki/Fibonacci_sequence)
(which starts 0, 1, 1, 2, 3, 5, and so on). You can run the executable with a
single number after it, like `./add_nums 3`, which will print out:

```
The sum of the squares of the first 1 Fibonacci numbers is 0
The sum of the squares of the first 2 Fibonacci numbers is 1
The sum of the squares of the first 3 Fibonacci numbers is 2
```

Unfortunately, there are _at least_ 5 bugs in this code that affect its
correctness: for certain inputs, the program will crash or provide incorrect
output due to these bugs. For this problem, you need to user your intuition and
GDB to identify any 4 bugs in the code and briefly report on each one.

In each bug, you should summarize:

- What the bug is: e.g., the `for` loop in `array_sum` starts at 1 instead of 0.
- What effect the bug has: e.g., the program crashes with a segmentation fault
  when called with `./add_num 0`.
- The steps you took in GDB to find/explore the bug: e.g., run the program with
  argument `42`, set a breakpoint in `main`, a watchpoint for `argc`, and
  stepped through `square` to examine the contents of the call stack.
- What change to the code would fix the bug: e.g., start the loop at 0, or add a
  check for a command-line argument of 0.

Please note the following rules and hints:

- All reported bugs need to be the result of running `add_nums`, not
  `add_nums_unsafe`.
- No code in `main` dealing with `argc` or `argv` will have any bugs.
- Some bugs have multiple possible fixes - you don't have to list all the fixes,
  just one.
- The documentation comments for functions have been left out - the intended
  effect of each function should be clear, but feel free to ask on Discord for
  clarification.

### 2.0. Setup

If you're on an ARM Mac and using VS Code, you'll need to reopen this project in
the Dev Container. Open the Command Palette (Cmd-Shift-P) and select "Dev
Containers: Reopen in Container".

For everyone, after you're set up, open a Terminal and change into the
`build/src` directory for this project. When you build/compile your code, you
can find the `add_nums` and `add_nums_unsafe` executables here, and run them
with GDB.

### 2.1. Compiler Options

As the CMake configuration for `src` shows, the `add_nums_unsafe` executable is
identical to `add_nums`, but with one compilation option added. This causes it
to have a slightly different effect on most systems.

If you run both (original, unfixed) programs with the same argument in GDB, you
should see in some cases that they both crash (i.e., do not terminate
successfully), but with different errors and in different places. Below, list
(1) the argument you provided both versions of the program, (2) any differences
in how the programs terminated in GDB, and (3) the backtrace of each program
when it stops running.

(Replace this line with your answer)

### 2.2. Bug 1

**What the bug is:**

(Replace this line with your answer)

**What effect the bug has:**

(Replace this line with your answer)

**The steps you took in GDB to find/explore the bug:**

(Replace this line with your answer)

**What change to the code would fix the bug:**

(Replace this line with your answer)

### 2.3. Bug 2

**What the bug is:**

(Replace this line with your answer)

**What effect the bug has:**

(Replace this line with your answer)

**The steps you took in GDB to find/explore the bug:**

(Replace this line with your answer)

**What change to the code would fix the bug:**

(Replace this line with your answer)

### 2.4. Bug 3

**What the bug is:**

(Replace this line with your answer)

**What effect the bug has:**

(Replace this line with your answer)

**The steps you took in GDB to find/explore the bug:**

(Replace this line with your answer)

**What change to the code would fix the bug:**

(Replace this line with your answer)

### 2.5. Bug 4

**What the bug is:**

(Replace this line with your answer)

**What effect the bug has:**

(Replace this line with your answer)

**The steps you took in GDB to find/explore the bug:**

(Replace this line with your answer)

**What change to the code would fix the bug:**

(Replace this line with your answer)

## 3. Submission

Make sure that you have run the appropriate formatters (clang-format and
Prettier) before submitting.

To submit this assignment, add and commit your changed files. These should be
some files in the `test` directory, this README file, and `src/add_nums.c`. Be
sure to write a reasonably clear commit message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
