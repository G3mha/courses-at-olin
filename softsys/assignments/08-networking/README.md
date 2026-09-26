# Assignment 8: Networking

In this assignment, your task is to write an _echo server_, which as its name
suggests, sends back any line a client sends it, verbatim. In building the
infrastructure to set this up, you'll learn a bit about socket programming, work
with the internals of file and network communication, and practice your skills
at error handling.

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
$ git switch -c assignment-08
```

### 0.2. Read the Rubric

The `rubric.md` file contains the rubric for this assignment. You should take a
look at the rubric (particularly the correctness portion) to get a sense of how
your submission will be evaluated.

## 1. Building an Echo-system

The `src/` directory has the required files for the server and client:

- `util.c` and `util.h` contain functions and variables used by both the server
  and the client, and has three unfinished functions.
- `server.h` and `server.c` contain the server code, which has three unfinished
  functions.
- `client.h` and `client.c` contain the client code, which has one unfinished
  function.
- `run_server.c` and `run_client.c` allow you to build and run the server and
  client yourself for testing.

You should implement the functions shown to get the server and client to work.
If all is successful, you should be able to start the server, then start one or
more clients. Once connected, you can type input into the client, and see each
line echoed back to you. You can then exit the client by pressing Ctrl-D, at
which point the client will exit without any additional output. The server can
be shut down with Ctrl-C.

The `.h` files specify the intended behavior of the functions, so you should
read the documentation comments to understand what each function should do.

As you do this, please note the following:

- Most of the functions you need to implement are very small - typically 5 lines
  or less. These functions essentially do one system call and then check for
  errors, exiting if necessary. The exceptions are the three functions in
  `server.c`.
- When implementing `socket_address`, you may see warnings about a field in
  `sockaddr_in` called `sin_zero`. This is field used for padding the
  `sockaddr_in` struct. If you want, you can manually zero out that value, but
  you can also use the field initializer (e.g., `{.foo = 42, .bar = "c"}`) to
  create the struct, since all fields left out are automatically set to zero.
- Make sure to properly use host vs network byte ordering in `sockaddr_in`
  structs, or you may not be able to connect the server with clients.
- In `accept_client`, you should use `accept4` rather than `accept` to connect a
  client. The function call is identical, except you should add a `SOCK_CLOEXEC`
  to the end (meaning if your `accept` call would be `accept(foo, bar, baz)`,
  you should instead call `accept4(foo, bar, baz, SOCK_CLOEXEC)`).
- In the reading, it is recommended that when you fork a process to handle the
  actual echoing of client input, you should close the server's listener socket
  in the child process after forking. **Don't do this**, as `run_server.c` is
  already set up to clean that socket up for you. If you try to close the socket
  anyway, you will get errors upon exiting the server.
- When implementing `echo` in `server.c`, it is recommended that you open a file
  pointer from the socket descriptor, which will let you use higher-level
  functions like `getline` and `fputs` rather than syscalls like `read` and
  `write` (though you can do this if you wish). If you use file pointers, note
  that you need to be able to both read and write the file, since the same
  socket is used to transmit and receive. To do this, you can open the file with
  the mode `"r+"`.
- If when running `run_server.c` you get an "Address already in use" error, you
  can see which processes are currently using the port by running
  `sudo lsof -i :4242`. This may show you some process IDs that you can then end
  to release the port back for use.

While you do not need to check for errors in this assignment, it is highly
recommended that you do so, because socket errors are easy to make and error
handling makes it far easier to find the source of the bug.

## 2. Submission

To submit this assignment, add and commit your changed files. These should be
some files in the `src` directory. Be sure to write a reasonably clear commit
message.

Once you have committed your changes, push them to origin (your fork of the
course repository) and open a pull request to **your `main` branch**. Assign the
team "olincollege/softsys-20XX-YY-assistant" as reviewers (with "XX" and "YY"
replaced with the appropriate year and term).

Then, submit the URL to that pull request on Canvas.
