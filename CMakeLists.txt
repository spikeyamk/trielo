cmake_minimum_required(VERSION 3.13)
project(trielo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(lib/fmt)

# Create a library target
add_library(trielo STATIC
    lib/trielo.cpp
)

target_link_libraries(trielo PUBLIC
	fmt::fmt
)

# Include the header files
target_include_directories(trielo
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/fmt/include
)

#add_executable(main PRIVATE main.cpp
#	lib/test.cpp
#	)

#target_include_directories(trielo_test PRIVATE
#	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
#	${CMAKE_CURRENT_LIST_DIR}/lib/fmt/include
#	)

#target_link_libraries(trielo_test PRIVATE
#	fmt::fmt
#	)	
