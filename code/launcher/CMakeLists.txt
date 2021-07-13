project(overboost-launcher)

add_executable(${PROJECT_NAME})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES}
)

if(WIN32)
	target_sources(${PROJECT_NAME}
		PRIVATE win/winquake.rc
	)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "launcher"
)