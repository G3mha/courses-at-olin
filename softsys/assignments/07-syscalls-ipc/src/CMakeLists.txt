add_library(string_array string_array.c string_array.h)

add_library(shell shell.c shell.h)
target_link_libraries(shell PUBLIC string_array)

add_executable(softshell softshell.c)
target_link_libraries(softshell PRIVATE shell)
