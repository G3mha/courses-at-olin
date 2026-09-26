# Assignment 9: Threading

In this assignment, your task is to write a small multithreaded program that
uses semaphores and mutexes to make certain concurrency guarantees. In doing so,
you'll learn a bit about implementing POSIX threads with concurrency primitives,
as well as think about ways to ensure that threads proceed without getting
deadlocked.

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
$ git switch -c assignment-09
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. No Thread Left Behind

In this problem, your task is to generalize the Rendezvous pattern to multiple
threads.

### 1.0. Recap on Rendezvous

In class, we saw the Rendezvous pattern, which makes sure that in two threads,
each thread completes its first step before either thread completes its second
step. For example, consider the following two threads.

Thread 1:

```c
puts("Step A1");
puts("Step B2");
```

Thread 2:

```c
puts("Step B1");
puts("Step A2");
```

To make sure that _both_ `Step A1` and `Step B1` are printed before _either_ of
`Step A2` or `Step B2` are printed, you can create two semaphores `sem_a` and
`sem_b` initialized to 0 and do the following.

Thread 1:

```c
puts("Step A1");
sem_post(&sem_a);
sem_wait(&sem_b);
puts("Step B2");
```

Thread 2:

```c
puts("Step B1");
sem_post(&sem_b);
sem_wait(&sem_a);
puts("Step A2");
```

This is a simple example, but it has useful applications. For example, two
threads processing data may want to make sure that memory has been allocated
appropriately for both threads before proceeding.

### 1.1. Weaving More Threads Together

In the `src/` directory, you will find `weave.c`, which tries to create threads
with a similar pattern to what we saw above. Specifically, the `start_threads()`
function starts up some number of threads, each of which runs a function called
`synchronize()`. That function in turn runs `ready()` and then `go()`.

You can run the code by building and running the `run_weave` program. In its
initial state, it will print output like this:

```
Thread 0 ready!
Thread 0 go!
Thread 1 ready!
Thread 1 go!
Thread 2 ready!
Thread 2 go!
```

Your goal is to rewrite `synchronize()` and `start_threads()` so that no thread
prints its `go!` message until all threads have printed their `ready!` message.
The threads do not have to print in order, so the following output would be
acceptable:

```
Thread 0 ready!
Thread 2 ready!
Thread 1 ready!
Thread 0 go!
Thread 1 go!
Thread 2 go!
```

To do this, you should use the appropriate concurrency primitives. To help you
in this task, we have implemented `ready()` and `go()` for you. In `weave.h`,
you will also find a struct called `thread_args`, which may also give you a hint
about what arguments to pass to your thread.

In `synchronize()`, you should run the tasks for a single thread, which
ultimately consist of running `ready()` and then `go()` with the appropriate
arguments. (You will need to add other code to make sure that it runs those
functions at the right times.)

In `start_threads`, you should initialize any necessary shared variables, create
the threads and their arguments, wait for each thread to complete, and then
clean up. Any dynamically allocated memory must be freed at the end of the
function.

For testing, you may change `run_weave.c`, but do not commit changes to it.

## 2. Submission

To submit this assignment, add and commit any changed files. These should be
files in the `src` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
