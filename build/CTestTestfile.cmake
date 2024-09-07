# CMake generated Testfile for 
# Source directory: /home/niko_std/projects/cpp/labs/SmartPtr
# Build directory: /home/niko_std/projects/cpp/labs/SmartPtr/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_smart_pointers "/home/niko_std/projects/cpp/labs/SmartPtr/build/test_smart_pointers")
set_tests_properties(test_smart_pointers PROPERTIES  _BACKTRACE_TRIPLES "/home/niko_std/projects/cpp/labs/SmartPtr/CMakeLists.txt;43;add_test;/home/niko_std/projects/cpp/labs/SmartPtr/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
