project(Overboost-engine)

file(GLOB PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/qcommon/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/client/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/server/*.c
)

add_library(${PROJECT_NAME} MODULE ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "engine"
)