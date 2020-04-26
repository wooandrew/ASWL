# CMakeLists.txt for the main project (DLL)

cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Engine
add_library(libaswl SHARED ${SOURCES})

include(GenerateExportHeader)
generate_export_header(libaswl)
