# Assignment 2: Strings and Buffers

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
$ git switch -c assignment-02
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. `string` Along

In this problem, you will try your hand at writing a few string utility methods
in C. The behavior of these functions are taken from
[Python's string methods](https://docs.python.org/3/library/stdtypes.html#string-methods).

All of the functions in this problem can be found in `string_utils.c` (where you
should implement the functions) and `string_utils.h` (where the functions are
declared). There are also files of the form `run_<function>.c` that exist solely
for you to test your implementations with strings of your choosing. You can
change these for testing, but you shouldn't commit the files. To change them
back before submission, you can use `git checkout run_<function>.c`.

### 1.1. Let's Start with `startswith`

The `startswith` function takes two strings, `str` and `substr`, and returns 1
if `str` starts with `substr` and 0 otherwise. For example, `theta` starts with
`the`, so `startswith("theta", "the")` would return 1. On the other hand,
`application` does not start with `apple`, so
`startswith("application", "apple")` would return 0.

As a note, any string starts with an empty string, and a string always starts
with itself. So `startswith("abc", "")` should return 1, as should
`startswith("abc", "abc")`.

Neither `str` or `substr` can be a
[`NULL` pointer](https://en.cppreference.com/w/c/types/NULL) (the rough
equivalent of Python's `None` for C pointers).

In the file `string_utils.c`, you will find the function definition. Write your
implementation there. In `string_utils.h`, you will also find the function
declaration. Write a documentation comment for the function there.

### 1.2. It `endswith` This

The `endswith` function is similar to `startswith`, but instead of determining
whether `str` starts with `substr`, it returns 1 if `str` ends with `substr` and
0 otherwise. For example, `lathe` ends with `the`, so `endswith("lathe", "the")`
woukd return 1. On the other hand, `reapply` does not end with `apple`, so
`endswith("reapply", "apple")` would return 0.

As in `startswith`, a string always ends with an empty string, and a string
always ends with itself, so `startswith("abc", "")` should return 1, as should
`startswith("abc", "abc")`. Similarly, neither `str` or `substr` can be `NULL`.

In the file `string_utils.c`, you will find the function definition. Write your
implementation there. In `string_utils.h`, you will also find the function
declaration. Write a documentation comment for the function there.

### 1.3. I Was `count`ing on This String

The `count` function takes a string `str` and counts the number of times that a
substring `substr` occurs. So `count("banana", "na")` would return 2. These are
_non-overlapping_ occurrences, meaning that, even though the substring `aa`
occurs three times in the string `aaaa` (starting at indices 0, 1, and 2), we
only count the ones that don't overlap with each other (ignoring the one at
index 1).

As with the previous functions, neither `str` nor `substr` can be the `NULL`
pointer, but they can be empty strings. **If `substr` is empty, then the
function should behave a bit differently** - it should return the length of
`str` plus one. This represents the number of empty strings that occur before,
between, or after characters.

In the file `string_utils.c`, you will find the function definition. Write your
implementation there. In `string_utils.h`, you will also find the function
declaration. Write a documentation comment for the function there.

As a hint, you may find some of the string methods in `string.h` helpful. (Don't
use `strtok`, though - that modifies the original string and won't be able to be
used here.)

### 1.4. There's No Good Clever Name for This One

The `strip` function takes three strings: some source text `src`, a destination
buffer `dst`, and a set of characters `chars` to strip from `src`. The function
places a copy of `src` into `dst`, with any leading or trailing characters in
`chars` removed. This means that if `src` is `abcdefghi` and `chars` is `abehi`,
then `dst` should contain `cdefgh` after the function runs. Notice that even
though `e` is in `src`, it does not get removed - only instances of the
characters that occur at the beginning or end of `src` do. If you want to see
other examples of this function, you can check the behavior in Python: define
strings called `src` and `chars`, and run `src.strip(chars)` - the answer will
be what the contents of `dst` should be afterwards.

You can assume that `src` and `dst` are not `NULL`. Also, you can assume that
`dst` will always have enough space to store the stripped string and the null
terminator. However, `chars` is allowed to be `NULL`, and as with the previous
function `count`, the `strip` function behaves slightly differently in this
case. If `chars` is `NULL`, then the function should strip any whitespace from
the start and end of `src`. Specifically, "whitespace" here is defined to be any
character for which the `isspace` function in `strings.h` would return 1. For
convenience, we have included the string of all whitespace characters for you as
`WHITESPACE` in `string_utils.h`.

The `string_utils.h` file contains a documentation comment for you, which we
encourage you to read. It describes the intended behavior of the function in
more detail. In `string_utils.c`, you will find the definition of the file.
Implement your function there.

### 1.5. (Extra Credit) A `split`ting Headache

_Be warned: the extra credit problem is probably on the more difficult side. It
can be a valuable experience, but it's by no means necessary, and you should
only consider working on it if you have the time and interest._

The `split` function behaves like its Python equivalent: given a source string
`src`, a destination array `dst`, and a separator string `sep`, it splits the
text in `src` into substrings using `sep` as the separator, and writes those
substrings into `dst`. To mark the end of the array, it uses a `NULL` pointer.

As a more fully worked out example, consider splitting a line of a CSV file. We
can define some variables like this:

```c
char* src = "raindrops,roses,whiskers on kittens,";
char dst[5][20];
char* sep = ",";
```

Then, after running `split(src, dst, sep)`, `dst` should be the array
`{"raindrops", "roses", "whiskers on kittens", "", NULL}`.

Notice that the separator (`,`) does not occur in the array. Also, since `src`
ends with a comma, there is an extra empty string at the end of the array before
the final `NULL` pointer.

The separator `sep` must be a non-empty string, and like previous parts of this
problem, you can assume that `src` and `dst` are not `NULL`. You can also assume
that `dst` is large enough to hold all of the substrings (including the final
`NULL`), and that each array in `dst` is large enough to hold the largest
substring that would be generated by the function.

There is also some unusual behavior: if `sep` is `NULL` (not empty), then the
string should be split by any amount of whitespace. You can again use the
`WHITESPACE` string in `string_utils.h` to determine whitespace, if you would
like. You should also feel free to write some helper functions, which you may
find useful.

If you complete this problem and want to test your code, be sure to uncomment
the relevant lines in `test/CMakeLists.txt` so that the unit tests will run.

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `src` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
