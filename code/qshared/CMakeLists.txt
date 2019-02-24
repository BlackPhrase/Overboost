project(Overboost-qshared)

file(GLOB PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})