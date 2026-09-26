add_library(weave weave.c weave.h)
target_link_libraries(weave PRIVATE pthread)

add_executable(run_weave run_weave.c)
target_link_libraries(run_weave PRIVATE weave pthread)
