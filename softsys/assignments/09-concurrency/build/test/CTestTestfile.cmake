# CMake generated Testfile for 
# Source directory: /workspaces/softsys-2025-01/assignments/09-concurrency/test
# Build directory: /workspaces/softsys-2025-01/assignments/09-concurrency/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_weave]=] "/workspaces/softsys-2025-01/assignments/09-concurrency/build/test/test_weave" "--verbose" "-j1")
set_tests_properties([=[test_weave]=] PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/softsys-2025-01/assignments/09-concurrency/test/CMakeLists.txt;13;add_test;/workspaces/softsys-2025-01/assignments/09-concurrency/test/CMakeLists.txt;0;")
add_test([=[test_memory]=] "valgrind" "--leak-check=full" "--error-exitcode=1" "/workspaces/softsys-2025-01/assignments/09-concurrency/build/src/run_weave")
set_tests_properties([=[test_memory]=] PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/softsys-2025-01/assignments/09-concurrency/test/CMakeLists.txt;18;add_test;/workspaces/softsys-2025-01/assignments/09-concurrency/test/CMakeLists.txt;0;")
