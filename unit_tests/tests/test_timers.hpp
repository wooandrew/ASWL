// ASWL::Timers Unit Tests

#pragma once

#ifndef ASWL_TIMERS_UNIT_TESTS
#define ASWL_TIMERS_UNIT_TESTS

#include <ASWL/timers.hpp>

#include <utility>
#include <exception>

std::pair<int, std::exception> TestET();
std::pair<int, std::exception> TestDT();
std::pair<int, std::exception> TestFPS();

#endif // !ASWL_TIMERS_UNIT_TESTS
