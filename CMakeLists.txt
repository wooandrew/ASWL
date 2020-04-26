# CMakeLists.txt for libaswl

cmake_minimum_required (VERSION 3.8)

set(PROJECT_VERSION "0.1")
project(ASWL VERSION ${PROJECT_VERSION})


# Set Project Properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Link
include_directories("${CMAKE_SOURCE_DIR}/root/include")
link_directories("${CMAKE_SOURCE_DIR}/lib")

# Directories
add_subdirectory(root)
add_subdirectory(sandbox)
