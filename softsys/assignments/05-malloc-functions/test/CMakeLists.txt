# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

add_executable(test_linked_list test_linked_list.c)
target_link_libraries(test_linked_list
    PRIVATE linked_list
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_linked_list
    COMMAND test_linked_list ${CRITERION_FLAGS}
)

add_test(
    NAME test_memory
    COMMAND ${CTEST_MEMORYCHECK_COMMAND} ${CTEST_MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:test_linked_list>
)
