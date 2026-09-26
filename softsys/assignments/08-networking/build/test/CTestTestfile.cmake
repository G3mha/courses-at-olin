# CMake generated Testfile for 
# Source directory: /workspaces/softsys-2025-01/assignments/08-networking/test
# Build directory: /workspaces/softsys-2025-01/assignments/08-networking/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_util]=] "/workspaces/softsys-2025-01/assignments/08-networking/build/test/test_util" "--verbose" "-j1")
set_tests_properties([=[test_util]=] PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/softsys-2025-01/assignments/08-networking/test/CMakeLists.txt;13;add_test;/workspaces/softsys-2025-01/assignments/08-networking/test/CMakeLists.txt;0;")
add_test([=[test_server]=] "/workspaces/softsys-2025-01/assignments/08-networking/build/test/test_server" "--verbose" "-j1")
set_tests_properties([=[test_server]=] PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/softsys-2025-01/assignments/08-networking/test/CMakeLists.txt;23;add_test;/workspaces/softsys-2025-01/assignments/08-networking/test/CMakeLists.txt;0;")
