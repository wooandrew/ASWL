# CMakeLists.txt for the main project (DLL)

cmake_minimum_required (VERSION 3.8)

# Lib
add_library(libaswl STATIC 

    "include/utilities.hpp"                 "src/utilities.cpp"
    "include/logger.hpp"                    "src/logger.cpp"
)
