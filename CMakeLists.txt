cmake_minimum_required(VERSION 3.8)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/libs
	${CMAKE_CURRENT_SOURCE_DIR}/code/common # TODO: find any better solution?
)

add_subdirectory(libs)
add_subdirectory(code)