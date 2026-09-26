# Require the CMake version matching what is included in the latest LTS version
# of Ubuntu, which at the time of writing is 22.04.
cmake_minimum_required(VERSION 3.22)

project(SoftSysShapes
  VERSION 1.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wconversion -Wunreachable-code")

set(CMAKE_C_CLANG_TIDY "clang-tidy")

add_subdirectory(src)

