project(overboost-renderer)

add_library(${PROJECT_NAME} MODULE)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

if(WIN32)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/win PROJECT_SOURCES_PLATFORM)
elseif(UNIX)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/unix PROJECT_SOURCES_PLATFORM)
elseif(MACOSX)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/macosx PROJECT_SOURCES_PLATFORM)
else()
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/null PROJECT_SOURCES_PLATFORM)
endif()

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES}
	PRIVATE ${PROJECT_SOURCES_PLATFORM}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "renderer"
)

target_link_libraries(${PROJECT_NAME} overboost-qshared)