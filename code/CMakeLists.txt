set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

add_subdirectory(qshared)
add_subdirectory(game_shared)
add_subdirectory(botlib)

add_subdirectory(cgame)
add_subdirectory(renderer)
add_subdirectory(ui)
add_subdirectory(q3_ui)

add_subdirectory(game)

add_subdirectory(engine)
add_subdirectory(launcher)