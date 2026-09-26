# Assignment 0: Introduction to Assignments

The purpose of this assignment is to introduce you the basic workflow of working
on and submitting an assignment for this course. In the process of doing this
assignment, you will gain a bit of experience with the following:

- Performing basic system setup for the course or assignment.
- Writing and running basic programs in C.
- Formatting and testing your code.
- Submitting your assignment using Git and Canvas.

## 0. Setup

Problem 0 on any assignment, if it exists, is there to help you get things set
up for an assignment. Here, we make sure that you have the correct tools
installed, and walk you through installing some other tools that you may need.

Please note that these instructions are for the course setup (i.e., Ubuntu 24.04
running on its own, through a VM or through WSL) _only_. It is certainly
possible to get this setup on other machines, but we cannot guarantee technical
support.

### 0.1. Set Up Your System

If you haven't completed the computational setup for this course, you should do
so now. The `ansible/` directory in this repository contains files for Ubuntu
and macOS that will set up your system with everything needed, which consists of
a toolchain to build C code (GCC), linting/formatting tools for C, a unit
testing library (Criterion), Docker for running code in containers, and Act for
testing code in Containers.

First, you'll need to install Ansible, which you can do with `sudo apt install
ansible` (Ubuntu) or `brew install ansible` (macOS). Then, run:

```
ansible-playbook -K <path_to_yml>
```

Where `<path_to_yml>` is the path to the appropriate `.yml` file for your OS.
You'll be asked for your password, and Ansible should handle the rest. You can
run this as many times as you want, since Ansible won't change things if a task
has already been done. If something goes wrong, ask for help on Discord.

### 0.2. Configure Your IDE

Next, you should set up VS Code so that it runs the clang-format/Prettier tools
every time you save a file, which will save you the trouble of running it
yourself. Press `Ctrl-,` to open your settings menu, then ensure that the
following settings are active. (You can search for each of these settings rather
than scrolling through all of the options.)

- "Files: Insert Final Newline" should be enabled.
- "Editor: Format on Save" should be enabled.
- "Prettier: Prose Wrap" should be set to "Always".

Then, open a C file. (If you need, you can create a new file with any name
ending in `.c`.) Open the Command Palette by pressing Ctrl-Shift-P and select
"Format Document With...", then select "clang-format".

### 0.3. (Optional) Open a Development Container

If you want to try a bit of a simplified setup as an alternative, or if your
setup has issues for whatever reason, you can use a development container to
write your code in just about the same environment we test in. All you need is
an installation of Docker on your machine and the Dev Containers extension for
VS Code.

Both the Ubuntu and macOS Ansible playbooks should install Docker and the VS
Code extension for you. Once you've done this, open VS Code to the main SoftSys
repo folder (called something like `softsys-20XX-YY`). Then, open the Command
Palette and run "Dev Containers: Reopen in Container". The first time you do
this, it can take a while (a few minutes) to start up the container. Once
successful, you should see something like "Dev Container: SoftSys Ubuntu" in the
lower-left corner of the VS Code window. Note that in general, you'll need to
start from the main SoftSys folder to open the container.

Then, to get started with an assignment, open the Command Palette again and
select "File: Open Folder...", then the folder of the assignment you want to
open. In this case, that's `assignments/00-intro-to-assignments`. You only need
to do this the first time - once you've opened the folder in a development
container, you should be prompted to do so when you open the folder in the
future, without needing to start from the main SoftSys folder.

## 1. `branch`-ing Out

This step is different from SoftDes, so be sure to follow these instructions
carefully.

We usually think of Git as maintaining a history of our files over time, but it
can actually maintain multiple different version histories within the same
repository. As an example, if you run `git fetch upstream` and
`git fetch origin` from your local copy, you will download the latest version
histories to your repository, but keep the version history of your local copy in
place. You can easily switch among these histories, which can be very convenient
if you are working on multiple features at once. Each version history is called
a _branch_.

For your first task in this assignment, you'll get your repository up to date
and then create a new branch in which you can work on this assignment.

### 1.0. Sync Up

Before making a new branch, it's important to make sure that you're up to date
with the latest changes in the upstream repository and in your fork. Pulling
changes into your repo after making a new branch is possible, but this is
discouraged, as tracking the changes you made in the branch is significantly
more difficult.

On the command line, navigate to your SoftSys repo and run the following
commands:

```
$ git switch main  # Make sure you are on the main branch
$ git pull  # Sync up with your fork of the course repo
$ git pull upstream main  # Sync up with the upstream copy of the course repo
```

Read the output of these commands and make sure that you are indeed up to date.
If you receive a message about a merge conflict or that you have files that
would be overwritten, then the command was not successful and you will have to
do some additional steps to sync your repo up. The output of this message will
usually tell you what command(s) you can run to address the issue, but feel free
to ask on Discord if you need additional help.

### 1.1. Create a New Branch

To see the current branches you have, as well as which one you are on, run the
following command from your local copy of the course repo:

```
$ git branch -a
```

This will show all branches in the repository, with an asterisk (`*`) next to
the branch you are currently on. (You can also see what branch you are on by
looking at the beginning of the output of `git status`.) The command also shows
which branches are remote, as they all start with `remotes/`.

You can also use `git branch` to create a new branch. The new branch will be a
copy of whatever branch you are currently on, though any changes you make after
that point will remain in its own branch.

For the purposes of this assignment, create a branch called `assignment-00` in
your local copy by running the following command:

```
$ git branch assignment-00
```

### 1.2. Switch to the New Branch

Once you have created the `assignment-00` branch, check what branch you are on:

```
$ git branch -a
```

You should see that though the `assignment-00` branch has been created, you are
still on the `main` branch. This is because creating a new branch does not
switch you over to it automatically. To do that, you need to use the command
`git switch`. Run the following command:

```
$ git switch assignment-00
```

Now if you run `git branch` or `git status`, you should see that you are on the
`assignment-00` branch.

(For future reference, the command `git switch -c foo` will both create a new
branch called `foo` and switch to it, which is a bit more convenient.)

Note that `git switch` may fail if you have changes that are unstaged or
uncommitted. You can save these changes by adding and committing them, or you
can temporarily sweep them away by running `git stash` (for staged changes) or
`git stash -u` (to include unstaged changes). To restore these changes (e.g.,
after switching branches), you can run `git stash pop`.

For the remainder of this assignment, we'll work in the `assignment-00` branch.
If on this or a future assignment you forget to switch to this branch before
doing work, there are fixes available, but they tend to be relatively
situation-specific. Therefore, you will need to ask for help on Discord (use the
`#github` channel).

## 2. CMake the Most of It

One way that C differs from Python is that to run code in C, you first need to
compile the source code to an executable that will run on your machine. The
reading shows one way of doing this: on the command line, you can run a command
like `gcc -o foo foo.c`, and then run `./foo`.

While this is a quick and simple way to run code that you have written in C, it
does not scale to larger programs, and is not representative of the way that
developers typically compile and run programs in C. For this course, we will
instead use CMake to compile and run our code. In this problem, we will walk you
through the process of compiling code with CMake and Make and running it through
VS Code and (optionally) the command line.

### 2.1. Select the GCC Kit

CMake can access a range of compilers, linkers, and other tools on your system
used to transform source code in C to an executable. A collection of these tools
used to build an executable is called a _toolchain_. In this course, we use the
GNU Compiler Collection (GCC) toolchain, which is included with many widely-used
Linux distributions (and referenced often in the reading). To make this happen
in VS Code, you need to select that toolchain within VS Code's CMake settings.
VS Code refers to toolchains as _kits_, so you will specifically tell VS Code to
select the right kit for this assignments (and future assignments/projects in
this course).

Make sure that you are in the directory for this assignment by either (1)
navigating to the `00-intro-to-assignments` folder on the command line and
running `code .`, or (2) selecting File -> Open Folder (Ctrl-K, then Ctrl-O on
WSL/Linux) within VS Code, then selecting the `00-intro-to-assignments` folder.

Then, in VS Code, open the Command Palette (Ctrl-Shift-P on WSL/Linux) and run
"CMake: Select a Kit" (or begin typing some of those words, and the search
should narrow down and let you select that item).

You should then see a list of available kits appear. Select a GCC kit, which may
appear as "GCC (Linux)" or something in the form "GCC 11.2.3". Once you select
this, you should see the kit you selected near the bottom left corner of your VS
Code window:

![Lower left corner of VS Code window showing the GCC toolchain
selected](img/kit_and_variant.png)

(Note that the GCC version you see here may differ from what is on your machine.
This is fine.)

### 2.2. Select the Debug Variant

Even within a specific toolchain/kit, CMake can set up different settings to
optimize the executable for different use cases. Two common use cases are a
"Debug" executable (slower but easier to analyze with a debugging tool) and a
"Release" executable (faster but difficult/impossible to analyze with a
debugging tool). For this course, you usually do not need to optimize your code
for performance, so you should set up CMake to build debug-optimized
executables. To do this in VS Code, you will need to tell CMake to build the
Debug variant.

In VS Code, open the Command Palette and select "CMake: Select Variant". Then
select "Debug". As with the previous step, near the bottom left corner of your
VS Code Window, you should see that CMake is set up to build the Debug variant:

![Lower left corner of VS Code window showing the Debug variant
selected](img/kit_and_variant.png)

### 2.3. Configure the Project Build

CMake on its own does not actually compile your code. Instead, it reads
configuration files (usually called `CMakeLists.txt` in different directories)
and uses that configuration to generate build files used by Make (called
`Makefile`). The process of generating this file is called _configuring_ the
build.

In the Command Palette of VS Code, search for and run the "CMake: Configure"
command. You may be asked to select a toolchain or kit; if you are, select the
latest GCC kit as described in a previous step.

If everything was successful, you should see output in VS Code that ends with
lines like this:

```
[cmake] -- Configuring done
[cmake] -- Generating done
[cmake] -- Build files have been written to: <softsys_repo_path>/assignments/00-intro-to-assignments/build
```

### 2.4. Build the Project

To actually compile code into executables or libraries, you need to build the
project. Your project can consist of different _targets_, each of which
represents a single executable or library. Make also uses special target names
that can refer to groups of targets, building multiple executables with a single
`make` command. In many setups, the default target is called `all`, and as its
name suggests, it builds every executable and library in the project. CMake has
this setup as well.

On the left side of the bottom bar of VS Code, you should see `[all]`, which
indicates that the current target to be build is `all`. Ensure that this is the
case.

Then, to build all of the targets, open the Command Palette and run the "CMake:
Build" command. Alternately, you can click on the "Build" button at the bottom
of your VS Code window, which has the same effect.

### 2.5. Run Hello World

To run the Hello World program that we have included as a test, click the "Play"
button (the triangle pointing to the right) at the bottom bar of your VS Code
window. You should see a terminal window open and the string `Hello World!`
printed there. If you see this, you are done with this problem!

### 2.6. (Optional) Configure, Build, and Run Manually

Sometimes, you may not have access to VS Code's integrated tools. Even if all
you have access to is the command line, it is possible to configure and build
projects with CMake and Make without much hassle. This step is optional, but you
may find it helpful to know how to configure, build, and run code manually.

First, you should navigate to the project root directory. For this assignment,
this is the `00-intro-to-assignments` folder. Make sure you are in this folder,
as the commands will not work if you are not.

#### 2.6.1. Create a Build Directory

To store all of the build configurations and executables built during the
compilation process, you should create a _build directory_. This directory holds
all of those files, preventing accidental overwrites of other files in your
project, and making it easy to start a fresh build (by deleting everything in
your build directory). To create this build directory, run the following
command:

```
$ mkdir build
```

This creates an empty directory called `build`. If you get an error that the
folder already exists (which may happen because VS Code generates this when
configuring your project), then you can remove the build directory and create a
fresh one:

```
$ rm -rf build
$ mkdir build
```

#### 2.6.2. Configure the Project

To configure your project, you need to run CMake. Because CMake outputs all of
the build files and configuration files in whatever directory you are in, you
should run the command from inside the build directory. To start, move into the
build directory:

```
$ cd build
```

However, when you run CMake, you need to tell it where to find the root-level
`CMakeLists.txt` configuration file, which contains information necessary to
configure your entire project (i.e., this assignment). To do that, run CMake but
specify that the root-level configuration file is in the project root, one
directory up from where you currently are:

```
$ cmake ..
```

You should see output similar to what you would see in VS Code when configuring
your project.

#### 2.6.3. Build the Code

To build the code, all you need to do is to run Make from the build directory:

```
$ make
```

You should again see output similar to what you would see in VS Code.

#### 2.6.4. Run the Code

By default, the compiled executables and libraries are arranged in the same way
as your source files (ending in `.c` or `.h`). This means that you can run the
`hello` executable from the folder where `hello.c` is located, but from the
build directory. To do this, run the following command:

```
$ ./src/hello
```

You should see the line `Hello, World!` printed in your terminal.

## 3. Your First Breath of Doxygen

Before you start writing any code in C, it's helpful to learn how to document
code, particularly functions. In this course, we will use the JavaDoc style for
comments, which was originally designed for Java but is also used for languages
with similar comment syntax (including C, C++, and PHP).

If you are familiar with Python, it's worth being aware of a quick clarification
on terminology: the term _docstring_ in Python is used to describe documentation
for a function, class, etc. In C, however, we tend to use the term
_documentation comment_ instead.

Here is an example of the documentation style that we will use for functions:

```c
/**
 * Convert a temperature from Celsius to Fahrenheit.
 *
 * Given a floating-point number representing a temperature in Celsius, return
 * its equivalent temperature in Fahrenheit. This function does not check for
 * temperatures lower than absolute zero (-273.15 degrees Celsius), so inputs
 * lower than this value can be converted without issue.
 *
 * @param celsius The temperature in degrees Celsius to convert.
 * @return A temperature equivalent to celsius, but in degrees Fahrenheit.
 */
float celsius_to_fahrenheit(float celsius);
```

Notice that comments begin with `/*` and end with `*/`. At the start of a
documentation comment, you should include two asterisks (`*`) and then start a
new comment line. The top of the documentation comment is a one-line description
of what the function does, followed by one or more optional paragraphs
describing the function in more detail. The one-line description is written in
the imperative, so it begins as "Convert..." rather than "Converts..." or "This
function converts...". Finally, it ends with tags of `@param` for each
parameter, followed by the name of the parameter and what it does, as well as a
single `@return` tag describing what the function's return value represents. If
a function takes `void` (no parameters) or returns `void` (returns nothing), the
corresponding tag(s) can be left off.

You may also notice that the function is not actually defined in the above
example. In C, you are allowed (but not required) to split the _declaration_ of
a function (describing the function's name, its parameters/types, and its return
type) and the _definition_ of a function (the code in the function body). We
tend to write the declarations in a separate file called the _header file_,
which ends in `.h` instead of `.c`. The file ending in `.c` is called the
_source file_. For any file `foo.h`, the corresponding file `foo.c` usually
contains the definitions of the functions. (The reason for this split will be
covered later in the course.)

In `string_utils.h`, you should find the declarations of three functions to
document. `string_utils.c` contains the corresponding definitions of those
functions. Read the definition of each function to determine what the function
is supposed to do, and add documentation comments above the _declarations_ of
the corresponding functions (i.e., in the header file) that follow the style
shown above.

## 4. C this New Language

C programming is not the focus of this assignment, but it's worth getting a bit
of practice writing simple function definitions in C. For this problem, we will
ask you to write three small functions in C, which you can then test and check
in the next problem.

### 4.1. Your Code is Absolutely Valued

In `absolute.c`, you will see a more or less empty definition of a function to
return the absolute value of a number. The function is already documented in
`absolute.h`, which you can read for specifics on how the function should be
implemented. In `absolute.c`, modify the function so that it has the correct
implementation.

### 4.2. Greeting Call

In `greet.c`, you will see a function `greet`. The `greet` function is
documented for you in `greet.h`. You will also see a `main` function in
`run_greet.c`. Implement the `greet` function in `greet.c`, then modify the
`main` function to set up and call `greet`. (To set up the function, you will
need to define a string to be used as your name - any plausible name will do.)

### 4.3. `switch` It Up

In `paths.c` you will see a functions `select_path`. The `select_path` function
is documented for in `paths.h`. You will also see a `main` function in
`run_paths.c`. Implement the `select_path` function using a `switch` statement.
Then modify the `main` function to read in a single numeric input from the user
(using `scanf`) and pass that to `select_path`.

## 5. Check for C-worthiness

Now that you have implemented some functions, it's time to check your code for
correctness and quality. Even outside this course, we encourage you to follow
these steps when writing C code.

### 5.1. Check Correctness with CTest and Criterion

CMake includes a testing command called CTest. CTest is not actually a unit test
framework - it just runs the tests in a convenient way. The actual unit test
framework we use is called Criterion. If you want to take a look at the those
tests, you can look at the `.c` files in the `test` directory of this
assignment.

You can run these tests by clicking the button at the bottom bar of VS Code that
says either "Run CTest" or "X/Y tests passing". This will open a window that
builds your code and runs the appropriate tests. At the bottom of this output,
if all of the tests pass, you should only see a few lines showing that your
tests pass. CTest counts the number of tests as the number of `.c` files in the
`test` directory, but each file contains multiple tests. If any tests fail, you
will see more detailed output from that file showing the specific tests that
failed.

If you prefer, you can also run the tests on the command line from the `build`
directory. There, run the following command to see the test output:

```
$ ctest --output-on-failure
```

For now, you do not need to know how to write these tests. All you need to do is
to run them and ensure that your function implementations from the previous part
are correct. If any tests do not pass, check the corresponding tests and your
code, and fix the function implementations so that the tests pass.

### 5.2. Check for Style with Clang-Tidy and a Clean Rebuild

Even though your code is correct, it might contain things that _might_ become
problems in the future. Depending on the specific issue, your code may end up
with bugs if used in a different context, or it may make it easier for you to
make a simple mistake. To check for and eliminate these, we will rebuild our
code from scratch and check it with the Clang-Tidy linter. Both of these can be
done at once with a single command.

In VS Code, open the Command Palette and select the command "CMake: Clean
Rebuild". This will compile all of your code from scratch. (By default, only
files that have changed get recompiled, so this is a way to make sure you didn't
miss any warnings during development.) You will see a window with the output of
the build process. Check and make sure that no lines containing the term
`warning:` appear in your output. If you do see those lines, read the message
and fix the issue. If you do not know how to fix an issue, ask for help on
Discord.

If you prefer, you can instead do this process from the command line. In the
`build` directory, run the following command:

```
$ make clean; make
```

This will delete all of the compiled code and rebuild everything from scratch.
Check the output for any warnings, and address them if necessary. As a bit of an
added convenience, most terminals tend to show colorized output, which will
allow you to see which warnings are from your compiler (the `warning` will be
colored differently) and which ones are from Clang-Tidy (no color in `warning`).

Once you have fixed all of the warnings, you are good to move on.

## 6. Submit the Assignment

Now you are ready to submit your assignment!

### 6.1. Commit Changes

Make sure that you are on the `assignment-00` branch first. If you are not,
switch to it with `git checkout`.

Stage your changes to this file using `git add`, then commit your changes using
`git commit`. If you need a more detailed walkthrough, the
[relevant reading on the SoftDes website](https://softdes.olin.edu/docs/readings/0-intro-to-assignments/#adding-and-removing-files)
may be helpful.

You are encouraged to write a reasonably non-vague commit message. It does not
have to be very detailed, but we should be able to look back at it and figure
out what the commit changed from the message. Optionally, you can see guidelines
for a good commit message on the
[Erlang GitHub wiki](https://github.com/erlang/otp/wiki/Writing-good-commit-messages)
(which we will revisit later in this course).

If you commit and then realized that you forgot to add some changes, you can
find steps for a fix on
[Oh Shit, Git](https://ohshitgit.com/#change-last-commit). The site also has
fixes for many other common scenarios.

### 6.2. Create Origin Branch and Push

When you go to push your changes the first time `git push`, you will likely get
an error message that asks you to create the branch on origin as well by running

```
$ git push --set-upstream origin assignment-00
```

Though this operation is referred to as setting an upstream branch, you are
actually creating a copy of your `assignment-00` branch on origin and not
upstream.

After doing this, you should be able to verify that your branch is visible on
your fork. You can visit
`https://github.com/USERNAME/softsys-20XX-YY/tree/assignment-00` (substituting
your username for `USERNAME`), where you should see your changes.

### 6.3. Open a Pull Request

To invite the course staff to review and provide feedback on your submission,
you can create a _pull request_ on GitHub. This is also a mechanism that is used
to propose changes to a repository (usually someone else's, but in this case,
yours).

To do this, visit the GitHub page for _your fork_ of the course repository.
There is a tab called "Pull requests", where you can see a button to open a new
pull request.

When setting up the new pull request, make sure you set the following options:

- base repository: `USERNAME/softsys-20XX-YY` (your local fork, not
  `olincollege/softsys-20XX-YY` as it is by default)

This will then open a new window with only two options for you to set:

- base: main
- compare: `assignment-00` (_not_ `main` as it might be by default)

You can then click to create the pull request.

Once you have created the pull request, look on the right sidebar for
"Reviewers". Select the "olincollege/softsys-20XX-YY-assistant" team and assign
them as reviewers.

### 6.4. Submit PR Link

Once you have created the pull request, you should be on a page with a URL in
the format `https://github.com/USERNAME/softsys-20XX-YY/pull/ZZ`, with your
username in place of `USERNAME` and a number in place of `ZZ` (likely 1). Copy
this URL.

The Canvas page for this assignment will ask you to submit a URL. Submit the URL
you copied above, and you are done!
