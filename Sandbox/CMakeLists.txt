cmake_minimum_required(VERSION 3.12)

project(Sandbox)


file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Engine
        spdlog::spdlog_header_only
        glfw
        glad::glad
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
)