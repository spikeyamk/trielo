cmake_minimum_required(VERSION 3.13)
project(trielo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_BUILD_TYPE)
	message("Trielo: CMAKE_BUILD_TYPE set")
else()
	set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(lib/fmt)

# Create a library target
add_library(trielo STATIC
    lib/trielo.cpp
)

target_link_libraries(trielo PRIVATE
	fmt::fmt
)

# Include the header files
target_include_directories(trielo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt/include
)

option(TRIELO_TEST "Enable Trielo Tests" OFF)

if(TRIELO_TEST)
	add_executable(run_all 
		tests/run_all.cpp
		tests/tests.cpp
	)

	target_include_directories(run_all 
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
		PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/fmt/include
	)

	target_link_libraries(run_all PRIVATE
		fmt::fmt
	)	

	add_executable(get_type_name 
		tests/get_type_name.cpp
		tests/tests.cpp
	)

	target_include_directories(get_type_name  
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
		PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/fmt/include
	)

	target_link_libraries(get_type_name PRIVATE
		fmt::fmt
	)	

	add_executable(get_func_name 
		tests/get_func_name.cpp
		tests/tests.cpp
	)

	target_include_directories(get_func_name  
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
		PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib/fmt/include
	)

	target_link_libraries(get_func_name PRIVATE
		fmt::fmt
	)	

	enable_testing()
	add_test(NAME Trielo::Tests::run_all
             COMMAND run_all)
	add_test(NAME Trielo::Tests::get_type_name
             COMMAND get_type_name)
	add_test(NAME Trielo::Tests::get_func_name
             COMMAND get_func_name)
endif()
