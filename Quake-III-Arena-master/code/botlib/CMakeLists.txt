project(Overboost-botlib)

add_definitions(-DBOTLIB)

file(GLOB PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
#add_library(${PROJECT_NAME} MODULE ${PROJECT_SOURCES})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#	OUTPUT_NAME "gladiator"
#)

#target_link_libraries(${PROJECT_NAME} Overboost-qshared)