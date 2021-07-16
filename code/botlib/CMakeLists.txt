project(overboost-botlib)

add_definitions(-DBOTLIB)

add_library(${PROJECT_NAME} STATIC)
#add_library(${PROJECT_NAME} MODULE ${PROJECT_SOURCES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES}
)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#	OUTPUT_NAME "gladiator"
#)

#target_link_libraries(${PROJECT_NAME} overboost-qshared)