add_executable(surprisal surprisal.c)
target_link_libraries(surprisal m)

add_library(shout shout.c shout.h)

add_library(array_sort array_sort.c array_sort.h)
