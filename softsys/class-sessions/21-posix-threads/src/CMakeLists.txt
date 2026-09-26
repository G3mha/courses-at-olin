add_executable(counters counters.c)
target_link_libraries(counters PRIVATE pthread)

add_executable(congress congress.c)
target_link_libraries(congress PRIVATE pthread)

add_executable(dQw4w9WgXcQ dQw4w9WgXcQ.c)
target_link_libraries(dQw4w9WgXcQ PRIVATE pthread)

add_executable(progress progress.c)
target_link_libraries(progress PRIVATE pthread)
