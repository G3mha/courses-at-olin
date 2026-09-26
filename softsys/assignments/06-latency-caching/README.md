# Assignment 6: Latency and Caching

In this assignment, your task is to optimize a small function to utilize a cache
well.

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
$ git switch -c assignment-06
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. Transpose for the Camera

In `src/transpose.c`, you will find a blank function called `transpose`. It
should implement a matrix transpose operation, in which `dst[j][i]` is assigned
to `src[i][j]` for all `i` and `j` in a matrix (a two-dimensional array).

The `transpose_ref` function contains a reference implementation of this
function, which will help you determine if you are implementing the function
correctly. As you can see, it uses `load` and `store` to access memory, which
you must do in your implementation of `transpose` as well.

You should implement `transpose` so that it has fewer cache misses than
`transpose_ref` does. To get full credit, you should beat `transpose_ref` by at
least 600 misses on our test case. To see the test case, you can either build
and run `src/run_transpose.c`, which has been provided to you for testing
purposes, or run the unit tests (which runs the same checks and reports a
failure if your implementation does not beat the reference implementation by
sufficient margin).

To make the checking of your code easier, we are not using your actual system's
cache, but rather a cache simulator. That code is in `src/cache.h` and
`src/cache.c`. When implementing `transpose`, you must access memory this way
and not by accessing memory directly. The `load` and `store` functions let you
read and write a value in memory, respectively, going through the simulated
cache.

### Cache Behavior

For this assignment, we have implemented a _direct-mapped cache_ for you. This
is a simple cache that has some number of lines, and an address of memory will
always be mapped to the same specific line of the cache. To do this, some bits
from the memory address are used to determine the _line index_ (which line of
the cache the memory will be placed in). Other bits form the _line offset_ (how
far into that line of memory the actual desired value is). Finally, the
remaining bits are used to form the _tag_, which helps identify what memory
address is stored in a line of the cache at any given time.

As an example, suppose that you have 16-bit addresses, the cache has 32 lines,
and each line is 8 bytes long. This means that to uniquely identify a line in
the cache, you need 5 bits (log base 2 of 32) and to identify an offset in the
cache line, you need 3 bits (log base 2 of 8). The bits of the address will be
split like this:

```
|       T       |    I    |  O  |
|0 0 1 0 1 0 1 1 0 1 1 0 0 1 1 1|

T: tag
I: line index
O: line offset
```

In this example, the address (which is `0x2b67` in hex) would be mapped to line
12 of the cache (`01100` in binary) and the desired byte would be in byte 7 of
the line (`111` in binary). The indexing for both of these would start from 0.
When this address is accessed and the cache does not have it, it is a cache
miss, and the cache will load the memory from `0x2b60` to `0x2b67` into the
line. The tag bits are used when checking the cache - if the cache already has a
line in the desired index, the tag bits help identify which specific part of
memory that line corresponds to.

All numerical values used in this assignment are single bytes, so you do not
need to worry about multi-byte values like ints crossing a line boundary.

### Explanation

Below, explain the code you wrote for the `transpose` function, and why it
results in better cache performance than the reference implementation. Your
explanation should be up to a paragraph (e.g., 3-5 sentences). You will be
graded on technical correctness of and clarity of your explanation.

(Replace this line with your answer)

### Extra Credit

For extra credit, you can try to optimize your implementation to see how many
fewer misses you get. For full credit, you need to beat the reference
implementation by at least 600 misses, but for every 500 misses further than
that, you will receive one extra credit point. There is a unit test in
`test_transpose.c` to determine how many points you receive. **Note that this
test always fails in order to print out the extra credit for our graders - this
does not indicate a failed implementation.**

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `test` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
