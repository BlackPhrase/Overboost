project(overboost-launcher)

if(WIN32)
	add_executable(${PROJECT_NAME} WIN32)
	
	target_sources(${PROJECT_NAME}
		PRIVATE win/winquake.rc
	)
else()
	add_executable(${PROJECT_NAME})
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "launcher"
)

target_link_libraries(${PROJECT_NAME} overboost-qshared)