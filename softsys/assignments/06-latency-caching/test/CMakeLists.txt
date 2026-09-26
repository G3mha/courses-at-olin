# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_cache test_cache.c)
target_link_libraries(test_cache
    PRIVATE cache
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_cache
    COMMAND test_cache ${CRITERION_FLAGS}
)

add_executable(test_transpose test_transpose.c)
target_link_libraries(test_transpose
    PRIVATE transpose cache
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_transpose
    COMMAND test_transpose ${CRITERION_FLAGS}
)

# add_test(
#     NAME test_memory
#     COMMAND ${CTEST_MEMORYCHECK_COMMAND} ${CTEST_MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:test_linked_list>
# )
