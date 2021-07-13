project(overboost-qshared)

file(GLOB PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE C_ONLY)