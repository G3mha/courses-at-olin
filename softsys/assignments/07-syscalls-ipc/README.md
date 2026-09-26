# Assignment 7: System Calls and Interprocess Communication

In this assignment, your task is to write a very simple, limited shell, called
SoftShell. By doing this, you'll learn a bit about some system calls, file
descriptors and basic interprocess communication.

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
$ git switch -c assignment-07
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. Don't Get Crabby

The `src/` directory has the required files for the shell. You will only be
editing `src/shell.c`, but we recommend that you read through the other files,
as they document data structures and functions that will be useful to you in
implementing your functions.

For this assignment, your job is to implement three functions: `process_tokens`,
`run`, and `process_command`. The `run` function is not tested on its own, as
its behavior is a key part of `process_command`.

The `.h` files specify the intended behavior of the functions. In addition to
reading the documentation comments for these functions, you should also take a
look at the tests in `test/test_shell.c`.

You may notice that there is a `string_array` struct with convenience functions.
Because part of running commands in this shell requires handling and processing
arrays of strings, we have implemented this struct for you. Keep in mind that
internally, the array of strings is stored in the usual way (as a `char**`), but
much of the memory management is taken care of for you. In addition, the string
array is guaranteed to end with a null pointer after its last element, which
serves a similar purpose to the null terminator of a string. (This may also be
helpful for some system calls that you will use in this assignment.)

The shell you are tasked with implementing has very limited capabilities -
specifically, it can only run programs on your path, which means that built-in
shell functions (which includes `cd`) will not work. If you want to see what
commands are built-in functions, you can type `which <function>` - if the result
is a file path, it should work in this shell.

This shell can also do basic file redirection, but only for input and output
files (no pipes), and only when formatted in a certain way. Specifically, if
your command redirects `foo.txt` to standard input and standard output to
`bar.txt`, the command must be written as

```
command <foo.txt >bar.txt
```

Note that there are no spaces after the `<` or `>` - however, these can occur
anywhere in the command (including at the beginning). That means that these
should all work:

```
<foo.txt command >bar.txt
>bar.txt <foo.txt command
command >bar.txt <foo.txt
```

You should handle these cases in the `process_tokens` function. Though we will
not check for this, **do not copy the pointer from `tokens` into the
`input_file` or `output_file` fields of the `command` struct** - this may cause
issues that are hard to debug (e.g., if those tokens are freed before the
command is used).

**You must also check for and handle errors when you call certain functions.**
The list of functions that this requirement applies to can be found in the
rubric.

### Correctness and Testing Notes

First, note that due to the way that temporary files are created during testing,
you might see a warning like this during compilation:

```
/usr/bin/ld: CMakeFiles/test_shell.dir/test_shell.c.o: in function `process_command_input_redirection_impl':
/softsys/assignments/07-syscalls-ipc/test/test_shell.c:162: warning: the use of `tempnam' is dangerous, better use `mkstemp'
```

This warning is because in between generating the temporary name and actually
creating the file, it's _technically_ possible to create another file with the
exact same name. But you can safely ignore this warning for this assignment, and
you won't lose any points for this warning.

Also, these temporary files are actually created on your machine during testing.
If you run the tests with `ctest --verbose`, you should see a message like this
in the output:

```
2: [RUN ] process_command::input_redirection
2: [----] Temporary input file: /tmp/ifileWBb7fY
...
2: [RUN ] process_command::output_redirection
2: [----] Temporary output file: /tmp/ofilejigghr
```

The characters at the end will be different, but anything in the form
`/tmp/ifileXXXXXX` is an input file redirected to your shell and anything in the
form `/tmp/ofileXXXXXX` is an output file your shell redirects to. You can look
at the contents of these files if it is helpful. Note that these files may be
deleted when your machine shuts down.

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `src` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
