add_library(square square.c square.h)

add_library(powmod powmod.c powmod.h)
target_link_libraries(powmod PRIVATE square)

add_executable(main main.c)
target_link_libraries(main PRIVATE square powmod)
