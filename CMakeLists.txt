cmake_minimum_required(VERSION 3.26)
project(trielo CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(trielo INTERFACE)

target_include_directories(trielo INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(TRIELO_TEST "Enable Trielo Tests" OFF)

if(TRIELO_TEST)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU|Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${PROJECT_NAME} PRIVATE /W4)
	endif()

	list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
	enable_testing()

	set(TEST_SRCS tests/tests.cpp)
	set(TEST_INCLUDE_DIRS ${TRIELO_INCLUDE_DIRS})

	function(add_test_case TEST_NAME TEST_SOURCE)
		add_executable(${TEST_NAME} ${TEST_SRCS} tests/${TEST_SOURCE})
		target_link_libraries(${TEST_NAME} trielo)
		add_test(NAME Trielo::Tests::${TEST_NAME}
				COMMAND ${TEST_NAME})
	endfunction()

	add_test_case(trielo_get_func_name get_func_name.cpp)
	add_test_case(trielo_get_type_name get_type_name.cpp)
	add_test_case(trielo_print_ostreamable print/ostreamable.cpp)
	add_test_case(trielo_print_nonostreamable print/nonostreamable.cpp)
	add_test_case(trielo_run_all run_all.cpp)
endif()