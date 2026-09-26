add_library(div div.c div.h)

add_executable(main main.c)
target_link_libraries(main PRIVATE div)
