# CMake generated Testfile for 
# Source directory: /Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/test
# Build directory: /Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_string_array]=] "/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/build/test/test_string_array" "--verbose" "-j1")
set_tests_properties([=[test_string_array]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/test/CMakeLists.txt;13;add_test;/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/test/CMakeLists.txt;0;")
add_test([=[test_shell]=] "/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/build/test/test_shell" "--verbose" "-j1")
set_tests_properties([=[test_shell]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/test/CMakeLists.txt;23;add_test;/Users/enriccogemha/Developer/softsys-2025-01/assignments/07-syscalls-ipc/test/CMakeLists.txt;0;")
