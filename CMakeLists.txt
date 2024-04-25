cmake_minimum_required(VERSION 3.26)
project(trielo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Create a library target
add_library(trielo INTERFACE)

set(TRIELO_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Include the header files
target_include_directories(trielo INTERFACE
	${TRIELO_INCLUDE_DIRS}
)

option(TRIELO_TEST "Enable Trielo Tests" OFF)

if(TRIELO_TEST)
	list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
	enable_testing()

	set(TEST_SRCS tests/tests.cpp)
	set(TEST_INCLUDE_DIRS ${TRIELO_INCLUDE_DIRS})

	function(add_test_case TEST_NAME TEST_SOURCE)
		add_executable(${TEST_NAME} ${TEST_SRCS} tests/${TEST_SOURCE})
		target_include_directories(${TEST_NAME} PRIVATE ${TEST_INCLUDE_DIRS})
		add_test(NAME Trielo::Tests::${TEST_NAME}
				COMMAND ${TEST_NAME})
	endfunction()

	add_test_case(trielo_get_func_name get_func_name.cpp)
	add_test_case(trielo_get_type_name get_type_name.cpp)
	add_test_case(trielo_print_ostreamable print/ostreamable.cpp)
	add_test_case(trielo_print_nonostreamable print/nonostreamable.cpp)
	add_test_case(trielo_run_all run_all.cpp)
endif()
