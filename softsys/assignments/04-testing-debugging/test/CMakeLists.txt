# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

add_executable(test_mean_correct test_mean.c)
target_link_libraries(test_mean_correct
    PRIVATE mean_correct m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_mean_correct
    COMMAND test_mean_correct ${CRITERION_FLAGS}
)

add_executable(test_mean_incorrect test_mean.c)
target_link_libraries(test_mean_incorrect
    PRIVATE mean_incorrect m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_mean_incorrect
    COMMAND test_mean_incorrect ${CRITERION_FLAGS}
)

add_executable(test_print_int_correct test_print_int.c)
target_link_libraries(test_print_int_correct
    PRIVATE print_int_correct m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_print_int_correct
    COMMAND test_print_int_correct ${CRITERION_FLAGS}
)

add_executable(test_print_int_incorrect test_print_int.c)
target_link_libraries(test_print_int_incorrect
    PRIVATE print_int_incorrect m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_print_int_incorrect
    COMMAND test_print_int_incorrect ${CRITERION_FLAGS}
)

add_executable(test_read_int_correct test_read_int.c)
target_link_libraries(test_read_int_correct
    PRIVATE read_int_correct m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_read_int_correct
    COMMAND test_read_int_correct ${CRITERION_FLAGS}
)

add_executable(test_read_int_incorrect test_read_int.c)
target_link_libraries(test_read_int_incorrect
    PRIVATE read_int_incorrect m
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_read_int_incorrect
    COMMAND test_read_int_incorrect ${CRITERION_FLAGS}
)
