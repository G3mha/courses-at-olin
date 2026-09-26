# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

# Homebrew on Apple Silicon puts headers and libraries into /opt/homebrew
# instead of /usr, so make sure that the Criterion libraries can be found on
# those machines.
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin"
    AND CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
  include_directories(BEFORE SYSTEM "/opt/homebrew/include")
  link_directories(BEFORE "/opt/homebrew/lib")
endif()

add_executable(test_count test_count.c)
target_link_libraries(test_count
  PRIVATE string_utils
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_count
  COMMAND test_count ${CRITERION_FLAGS}
)

add_executable(test_startswith test_startswith.c)
target_link_libraries(test_startswith
  PRIVATE string_utils
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_startswith
  COMMAND test_startswith ${CRITERION_FLAGS}
)

add_executable(test_endswith test_endswith.c)
target_link_libraries(test_endswith
  PRIVATE string_utils
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_endswith
  COMMAND test_endswith ${CRITERION_FLAGS}
)

add_executable(test_strip test_strip.c)
target_link_libraries(test_strip
  PRIVATE string_utils
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_strip
  COMMAND test_strip ${CRITERION_FLAGS}
)

# Uncomment the lines below to run tests for the split function.
# add_executable(test_split test_split.c)
# target_link_libraries(test_split
#   PRIVATE string_utils
#   PUBLIC ${CRITERION}
# )
# add_test(
#   NAME test_split
#   COMMAND test_split ${CRITERION_FLAGS}
# )
