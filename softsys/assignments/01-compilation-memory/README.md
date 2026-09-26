# Assignment 1: Compilation and Memory

In this assignment, you will get the chance to play with the compilation process
in C some more. You will also get to try your hand at implementing more complex
C functions that make use of memory and pointers.

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
$ git switch -c assignment-01
```

### 0.2. Read the Rubric

Assignments from this point forward will have rubrics. They are there to give
you an idea of how your work will be assessed, what is expected of you, and what
you can expect to get feedback on. You can complete the assignment without
reading it, but we strongly recommend that you read it to get a sense of how
assignments are graded.

The `rubric.md` file contains the rubric for this assignment. You can expect
this rubric to look largely the same from assignment to assignment.

## 1. Worst-Of Compilation

As a quick recap, here are the steps of the compilation as described in Think
OS.

1. Preprocessing
2. Parsing
3. Static checking
4. Code generation
5. Linking
6. Optimization

In this problem, you will take a C program that compiles successfully and change
it in such a way that the compilation process fails at various steps above.

In the file `surprisal.c`, you will see a program that you can compile and run.
Your job is to introduce bugs to the program in `surprisal.c` that causes the
compilation to fail during preprocessing, parsing, static checking, or linking.

In the `compilation.md` file, you will find four questions. Answer the questions
there.

After you are done, you should make sure that `surprisal.c` is back to its
starting state. You can do this in Git by running the following command from
this directory:

```
$ git restore src/surprisal.c
```

## 2. This Program Just `fgets` Me

The `scanf` function is one of the more abused functions in C. Partly, this is
due to the fact that it is intended to read structured input and has few
safeguards if anything goes wrong during the process of reading that input.
Additionally, even though it is designed to read highly structured input, it is
often used in lessons to read data from standard input, which can be just about
anything. The result is that many C programs use `scanf` where they should not,
leading to vulnerable programs whose behavior can be manipulated with clever
inputs. (We'll see more of this later in the course.)

The solution to this problem is to use the `fgets` function when reading data
from standard input. Essentially, `fgets` allows the program to read a single
line of text, up to a maximum number of characters, and store the read
characters in a string. The program can then copy, split up, or modify that
string however it wants, generally leading to safer behavior.

In this problem, you will use `fgets` to implement a function, and get a bit of
practice with some simple functions from the C standard library.

The files `shout.c` and `shout.h` contain the code you will need for this
problem. You should write the implementation of the `shout` function in
`shout.c`. This function should use `fgets` to read a line from standard input
that is a maximum of 32 characters, and store that in a string. It should then
change every lowercase character (`a` through `z`) in that string to its
uppercase equivalent (`A` to `Z`), and then print the changed string to standard
output.

In `shout.h`, you will find an _enum_, which is (among other things) a clean way
of declaring integer constants in modern C. Here is where the maximum number of
characters read by `fgets` is defined. You will also find the declaration of the
`shout` function here, along with its documentation comment.

It is easy to make subtle mistakes while writing this function due to
[the way that `fgets` works](https://en.cppreference.com/w/c/io/fgets). You are
**strongly** encouraged to read the documentation for the function. Keep the
following important points in mind:

- The variable `stdin` is found in `<stdio.h>`.
- You pass a parameter called `count` to `fgets` that tells it how many
  characters to read at maximum, but make sure you know how many characters the
  function actually reads.
- Remember that `fgets` can read a line of input (ending with a newline
  character, `'\n'`) or a maximum number of characters. You should read the
  documentation to know exactly what `fgets` stores in the array in these cases.
- You do not have to any error checking of `fgets`.
- If successful, `fgets` returns a character pointer; specifically, the string
  where it stores the input. Because you pass that string to `fgets`, you do not
  necessarily need to do anything with the return value of `fgets`. If you want
  to throw away the result of the `fgets` call, make it `void` like this to
  avoid compiler warnings: `(void)fgets(...)`.
- There are many ways to convert lowercase to uppercase characters, but you
  might find it helpful to read the
  [documentation on strings in C](https://en.cppreference.com/w/c/string/byte).
  You are likely to need to include `<ctype.h>`.

## 3. Sorting Out Some Arrays

In typical computer science courses, the problem of sorting a list of numbers is
considered fundamental in learning data structures and algorithms. Most
languages have a sorting function - in Python, you can use `sort` or `sorted`:

```python
numbers = [3, 1, 4]
sorted(numbers)  # Returns [1, 3, 4], but numbers is still [3, 1, 4]
numbers.sort()  # Sorts numbers in place, so it is now [1, 3, 4]
```

Even C, with its aggressively minimalist library, has the function `qsort`. But
it's made to handle arbitrary data types and comparisons, so you need to set up
a decent amount of infrastructure of your own to use it, even to sort a list of
`int`s:

```c
#include <stdlib.h>

int compare(const void* left_ptr, const void* right_ptr) {
  int left_int = *left_ptr;
  int right_int = *right_ptr;
  if (left_int < right_int) {
    return -1;
  }
  if (left_int > right_int) {
    return 1;
  }
  return 0;
}

int main(void) {
  int numbers[] = {3, 1, 4};
  qsort(numbers, 3, sizeof(int), compare);
  return 0;
}
```

...yeah.

In this problem, we will assume that we are working with an array of `int`s, and
write code to implement a simple sorting algorithm. It isn't a fast algorithm,
because that isn't the focus of this problem. The problem is more to get some
practice working with pointers and arrays.

### Document Functions

In `array_sort.h`, you will find three functions: `swap`, `sort_inplace`, and
`sort_copy`. Before you start implementing these functions, it is helpful to
make sure you understand what they are supposed to do. To practice this helpful
habit, we will start by asking you to first write documentation comments for
each of these functions.

The `swap` function takes two `int` pointers, and swaps the _integers_ pointed
to by these pointers. For example, if `left_ptr` points to 42 and `right_ptr`
points to 47 (wherever they are stored), then after `swap` runs successfully,
`left_ptr` should point to 47 and `right_ptr` should point to 42. The pointers
themselves will still point to the same place in memory after the function runs;
you should not need to create any new pointers. But the integers at those
locations should have switched places.

The `sort_inplace` function, as its name suggests, sorts an array of integers in
place. It takes the array to sort, as well as the number of integers in that
array (its size). As a side note, the
[`size_t` type](https://en.cppreference.com/w/c/types/size_t) is a special
unsigned integer type (it cannot be negative) that takes up enough bytes to hold
any value returned by the `sizeof` operator. After this function runs
successfully, the numbers in `numbers` should be sorted from least to greatest.

The `sort_copy` function takes an array of numbers called `numbers`, as well as
another array of numbers designed to hold the sorted copy of `numbers`. It also
takes an array size, as with `sort_inplace`. After `sort_copy` runs
successfully, `numbers` should still be what it was before running the function,
but `sorted` should contain the same integers arranged from least to greatest.

In `array_sort.h`, write documentation comments for the above three functions in
your own words. Follow the documentation comment style that you saw in the
previous assignment.

### Implement Functions

In `array_sort.c`, you will find the same three functions with empty
implementations. Replace the comments with an implementation of each of the
three functions.

For implementing `sort_inplace`, you should use the following algorithm:

- Start with Index 0 of the array (the position of the first integer).
- Iterate from Index 1 of the array to the end, and at each step, compare the
  integer in Index 0 to the integer at the current index.
- If the integer at the current index is smaller than what you have in Index 0,
  swap the two integers. At the end of this process, the integer at Index 0 will
  be the smallest integer in the array.
- Repeat the above steps, but now take Index 1, and iterate from Index 2 to the
  end, swapping integers when you find a smaller one. This will result in the
  integer at Index 1 being the second smallest integer in the array, so the
  first two integers of the sorted array will be in place.
- Repeat these steps for the remainder of the array, each time increasing your
  starting index by 1 until you have reached the end of the array.

For implementing `sort_copy`, you can use the algorithm of your choice. But an
easy way to do this is to copy every element from `numbers` into `sorted`, and
then run `sort_inplace` on `sorted`. You are allowed to implement the function
this way if you want.

It should go without saying, but you cannot use `qsort` in your implementation.

Unit tests are included for you to test each of these functions. The
`test/test_array_sort.c` file contains the actual tests if you want to take a
look, though when you run the tests, the output will show you each failed test.

## 4. Submission

To submit this assignment, add and commit your changed files. These should be
`compilation.md` and some files in the `src` directory. Be sure to write a
reasonably clear commit message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers.

Then, submit the URL to that pull request on Canvas.
