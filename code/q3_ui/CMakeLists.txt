project(overboost-q3_ui)

file(GLOB PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} MODULE ${PROJECT_SOURCES})

target_sources(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ui/ui_syscalls.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "q3ui"
)

target_link_libraries(${PROJECT_NAME} overboost-qshared overboost-game_shared)