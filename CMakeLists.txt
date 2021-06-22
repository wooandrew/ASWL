# CMakeLists.txt for libaswl

cmake_minimum_required (VERSION 3.8)

set(PROJECT_VERSION "0.4.0")
project(ASWL VERSION ${PROJECT_VERSION})


# Set Project Properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable Unicode
add_definitions(-UNICODE)
add_definitions(-D_UNICODE)

# Link
include_directories("${CMAKE_SOURCE_DIR}/root/include")

# link_directories("${CMAKE_SOURCE_DIR}/lib")

# Directories
add_subdirectory(root)
add_subdirectory(sandbox)
add_subdirectory(unit_tests)
