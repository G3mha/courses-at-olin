# Worst-Of Compilation

## 1. Preprocessing Error

What change to `surprisal.c` would cause an error during preprocessing? What is
that error?

Answer:

That could happen if, for example, we remove the `#include <stdio.h>` line. The error would be:

```bash
$ gcc surprisal.c
surprisal.c:16:5: error: call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
   16 |     printf("The surprisal of an event with probability %.2f is %.3f bits.\n",
      |     ^
surprisal.c:16:5: note: include the header <stdio.h> or explicitly provide a declaration for 'printf'
1 error generated.
```

## 2. Parsing/Syntax Error

What change to `surprisal.c` would cause an error during parsing? What is that
error?

Answer:

Parsing verifies the adherence to the syntax of the language. So, for example, if we remove the semicolon at the end of the line 8, we would get a parsing error:

```bash
$ gcc surprisal.c
surprisal.c:8:21: error: expected ';' after return statement
    8 |   return -log2(prob)
      |                     ^
      |                     ;
1 error generated.
```

## 3. Static Checking Error

What change to `surprisal.c` would cause an error during static checking? What
is that error?

Answer:

Static checking is about verifying the set of semantic constraints of the language, therefore, the coherence of the code, without running it. For example, calling the function `surprisal()` without passing any parameters in line 16, would be a static checking (semantic) error:

```bash
$ gcc surprisal.c
surprisal.c:17:28: error: too few arguments to function call, single argument 'prob' was not specified
   17 |            prob, surprisal());
      |                  ~~~~~~~~~ ^
surprisal.c:4:8: note: 'surprisal' declared here
    4 | double surprisal(double prob) {
      |        ^         ~~~~~~~~~~~
1 error generated.
```

## 4. Linking Error

What change to `surprisal.c` would cause an error during linking? What is that
error?

Answer:

Linking is about resolving the references to functions and variables. Declaring a function but not defining it would cause a linking error. For example, if we remove the definition of the function `surprisal()`, and just leave the declaration, that generates a linking error:

```bash
$ gcc surprisal.c
Undefined symbols for architecture arm64:
  "_surprisal", referenced from:
      _main in surprisal-92ecb4.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```
