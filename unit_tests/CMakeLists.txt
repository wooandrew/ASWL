# CMakeLists.txt for libaswl's sandbox env

cmake_minimum_required (VERSION 3.8)

add_library(tests 
    "tests/test_timers.hpp" "tests/test_timers.cpp"
)

add_executable(unit_tests unit_tests.cpp)

target_link_libraries(unit_tests PRIVATE tests)
target_link_libraries(unit_tests PRIVATE libaswl)
