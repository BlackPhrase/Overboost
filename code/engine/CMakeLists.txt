project(overboost-engine)

add_library(${PROJECT_NAME} MODULE)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

#target_sources(${PROJECT_NAME}
	#PRIVATE ${PROJECT_SOURCES}
#)

add_subdirectory(qcommon)
add_subdirectory(client)
add_subdirectory(server)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "engine"
)

target_link_libraries(${PROJECT_NAME} overboost-botlib overboost-qshared)