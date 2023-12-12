# CMake generated Testfile for 
# Source directory: /home/spikeyamk/trielo
# Build directory: /home/spikeyamk/trielo/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Trielo::Tests::run_all "/home/spikeyamk/trielo/build/run_all")
set_tests_properties(Trielo::Tests::run_all PROPERTIES  _BACKTRACE_TRIPLES "/home/spikeyamk/trielo/CMakeLists.txt;74;add_test;/home/spikeyamk/trielo/CMakeLists.txt;0;")
add_test(Trielo::Tests::get_type_name "/home/spikeyamk/trielo/build/get_type_name")
set_tests_properties(Trielo::Tests::get_type_name PROPERTIES  _BACKTRACE_TRIPLES "/home/spikeyamk/trielo/CMakeLists.txt;76;add_test;/home/spikeyamk/trielo/CMakeLists.txt;0;")
add_test(Trielo::Tests::get_func_name "/home/spikeyamk/trielo/build/get_func_name")
set_tests_properties(Trielo::Tests::get_func_name PROPERTIES  _BACKTRACE_TRIPLES "/home/spikeyamk/trielo/CMakeLists.txt;78;add_test;/home/spikeyamk/trielo/CMakeLists.txt;0;")
subdirs("lib/fmt")
