add_library(cache cache.c cache.h)

add_executable(run_cache run_cache.c)
target_link_libraries(run_cache cache)

add_library(transpose transpose.c transpose.h)
target_link_libraries(transpose PUBLIC cache)

add_executable(run_transpose run_transpose.c)
target_link_libraries(run_transpose PRIVATE cache transpose)
