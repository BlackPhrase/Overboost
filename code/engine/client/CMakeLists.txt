aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES_CLIENT)

set(PLATFORM "null")

if(WIN32)
	set(PLATFORM "win")
elseif(APPLE) #(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(PLATFORM "macos")
elseif(UNIX)
	set(PLATFORM "unix")
endif()

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../qcommon/${PLATFORM}
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM} PROJECT_SOURCES_CLIENT_PLATFORM)

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES_CLIENT}
	PRIVATE ${PROJECT_SOURCES_CLIENT_PLATFORM}
)