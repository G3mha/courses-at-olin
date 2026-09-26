# CMake generated Testfile for 
# Source directory: /Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/test
# Build directory: /Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_linked_list]=] "/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/build/test/test_linked_list" "--verbose" "-j1")
set_tests_properties([=[test_linked_list]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/test/CMakeLists.txt;11;add_test;/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/test/CMakeLists.txt;0;")
add_test([=[test_memory]=] "/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/build/test/test_linked_list")
set_tests_properties([=[test_memory]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/test/CMakeLists.txt;23;add_test;/Users/enriccogemha/Developer/softsys-2025-01/assignments/05-malloc-functions/test/CMakeLists.txt;0;")
