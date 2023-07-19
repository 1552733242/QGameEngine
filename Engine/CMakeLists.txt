cmake_minimum_required(VERSION 3.12)

project(Engine)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE HEAD_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.h)

add_library(${PROJECT_NAME} SHARED
    ${SRC_FILES}
    ${HEAD_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/src/QGame
        ${CMAKE_CURRENT_LIST_DIR}/src/Events
        ${CMAKE_CURRENT_LIST_DIR}/src/Platiform
        ${CMAKE_CURRENT_LIST_DIR}/src/Platiform/Windows
)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog_header_only
        glfw
        glad::glad
)


target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        GAME_PLATFORM_WINDOWS
    PRIVATE
        GAME_BUILD_DLL
)




target_precompile_headers(${PROJECT_NAME}
    PRIVATE
        <iostream>
        <memory>
        <algorithm>
        <functional>
        <string>
        <sstream>
        <vector>
        <unordered_map>
        <unordered_set>
        ${CMAKE_CURRENT_LIST_DIR}/src/QGame/Core.h
        ${CMAKE_CURRENT_LIST_DIR}/src/QGame/Log.h
)

