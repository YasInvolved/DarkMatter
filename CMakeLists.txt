cmake_minimum_required(VERSION 3.31)
project(DarkMatter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(DM_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
get_filename_component(DM_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}" ABSOLUTE)

add_subdirectory(3rdparty/SDL)

add_subdirectory(src/DarkMatter)
add_subdirectory(SandboxGame)