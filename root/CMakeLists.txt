# CMakeLists.txt for the main project (DLL)

cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

# Lib
add_library("libaswl-static-debug" STATIC 
    "include/utilities.hpp"         "src/utilities.cpp"
    "include/logger.hpp"            "src/logger.cpp"
)
add_library("libaswl-shared-debug" SHARED 
    "include/utilities.hpp"         "src/utilities.cpp"
    "include/logger.hpp"            "src/logger.cpp"
)


include(GenerateExportHeader)
generate_export_header("libaswl-static-debug")
