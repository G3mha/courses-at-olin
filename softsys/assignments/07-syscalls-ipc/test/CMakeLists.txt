# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion -Wno-int-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_string_array test_string_array.c)
target_link_libraries(test_string_array
    PRIVATE string_array
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_string_array
    COMMAND test_string_array ${CRITERION_FLAGS}
)

add_executable(test_shell test_shell.c)
target_link_libraries(test_shell
    PRIVATE shell
    PUBLIC string_array ${CRITERION}
)
add_test(
    NAME test_shell
    COMMAND test_shell ${CRITERION_FLAGS}
)
