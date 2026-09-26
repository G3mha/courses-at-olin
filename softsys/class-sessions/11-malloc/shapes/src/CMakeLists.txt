add_library(rectangle rectangle.c rectangle.h)

add_executable(main main.c)
target_link_libraries(main PRIVATE rectangle)
