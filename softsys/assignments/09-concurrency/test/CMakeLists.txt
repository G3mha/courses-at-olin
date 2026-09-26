# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion -Wno-int-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_weave test_weave.c)
target_link_libraries(test_weave
   PRIVATE weave
   PUBLIC ${CRITERION}
)
add_test(
   NAME test_weave
   COMMAND test_weave ${CRITERION_FLAGS}
)

add_test(
   NAME test_memory
   COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:run_weave>
)

