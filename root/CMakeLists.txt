# CMakeLists.txt for the main project (DLL)

cmake_minimum_required (VERSION 3.8)

# Lib
add_library(libaswl STATIC 

    "include/ASWL/aswl.hpp"
    "include/ASWL/utilities.hpp"                "src/utilities.cpp"
    "include/ASWL/logger.hpp"                   "src/logger.cpp"
    "include/ASWL/timers.hpp"                   "src/timers.cpp"
    )
