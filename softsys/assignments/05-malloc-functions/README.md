# Assignment 5: Linked Lists

In this assignment, your task is to implement a linked list. In the process of
doing so, you will gain some experience with dynamic memory management using
`malloc` and `free`, using function pointers, and implementing variadic
functions.

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
$ git switch -c assignment-05
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. Making a `list` and Checking It Twice

In `src/linked_list.h`, you will find the descriptions of a variety of linked
list functions. You should implement these functions in `src/linked_list.c`. The
`node`-related functions have already been implemented for you.

If you need details on what each function should do or return, read the
documentation comment for the function. As you implement these functions, you
should feel free to use any of the functions to help implement other functions
(and you are encouraged to do so, as it can make the implementation
significantly simpler in some cases).

To check the correctness of your code, you can run the tests in
`test/test_linked_list.c` in the usual way.

Because the linked list uses dynamically allocated memory, there is also a
memory test run with Valgrind to make sure that your code is not leaking memory.
Note: **this test always passes due to the way Valgrind is implemented, so you
need to check the output manually**. To do this, check to see if any of the
Valgrind outputs (not just the bottom one) show lost bytes on the heap.

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `test` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
