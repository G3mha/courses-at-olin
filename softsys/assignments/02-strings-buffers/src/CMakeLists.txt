add_library(string_utils string_utils.c string_utils.h)

add_executable(run_startswith run_startswith.c)
target_link_libraries(run_startswith PRIVATE string_utils)

add_executable(run_endswith run_endswith.c)
target_link_libraries(run_endswith PRIVATE string_utils)

add_executable(run_count run_count.c)
target_link_libraries(run_count PRIVATE string_utils)

add_executable(run_strip run_strip.c)
target_link_libraries(run_strip PRIVATE string_utils)

add_executable(run_split run_split.c)
target_link_libraries(run_split PRIVATE string_utils)
