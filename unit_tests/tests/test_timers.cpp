// ASWL::Timers Unit Tests

#define __ASWL_SILENCED
#include "test_timers.hpp"
#include "test.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

std::pair<int, std::exception> TestET() {

    ASWL::Timers::ElapsedTime et;

    try {

        std::clog << "UNIT_TEST:  ASWL::TIMERS::ELAPSEDTIME:\t\t";

        et.start();

        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (std::round(et.now()) != 2.f)
            throw ASWL::Timers::time_exception("ELAPSED TIME DOES NOT MATCH! 1 now()");

        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (std::round(et.lap()) != 4.f)
            throw ASWL::Timers::time_exception("ELAPSED TIME DOES NOT MATCH! lap()");

        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (std::round(et.now()) != 2.f)
            throw ASWL::Timers::time_exception("ELAPSED TIME DOES NOT MATCH! 2 now()");

        et.stop();

        et.now();
    }
    catch (ASWL::Timers::time_exception& e) {
        return { 0, no_exception() };
    }
    catch (std::exception& e) {
        return { -1, e };
    }

    return { -1, std::runtime_error("UNEXPECTED ERROR OCCURED!")};
}

std::pair<int, std::exception> TestDT() {

    ASWL::Timers::DeltaTime dt;

    try {

        std::clog << "UNIT_TEST:  ASWL::TIMERS::DELTATIME:\t\t";
        
        dt.UpdateDeltaTime();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        dt.UpdateDeltaTime();
        
        if (std::floor(dt.GetDeltaTime()) != 2.f)
            throw std::runtime_error("DELTA TIME DOES NOT MATCH! 2s");


        dt.UpdateDeltaTime();
        std::this_thread::sleep_for(std::chrono::seconds(4));
        dt.UpdateDeltaTime();

        if (std::floor(dt.GetDeltaTime()) != 4.f)
            throw std::runtime_error("DELTA TIME DOES NOT MATCH! 4s");

        dt.UpdateDeltaTime();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        dt.UpdateDeltaTime();

        if (std::floor(dt.GetDeltaTime()) != 10.f)
            throw std::runtime_error("DELTA TIME DOES NOT MATCH! 10s");
    }
    catch (std::exception& e) {
        return { -1, e };
    }
        

    return { 0, no_exception() };
}

std::pair<int, std::exception> TestFPS() {

    ASWL::Timers::FramesPerSecond fps;

    try {

        std::clog << "UNIT_TEST:  ASWL::TIMERS::FRAMESPERSECOND:\t";

        fps.Update(true);
        for (int i = 0; i < 10; i++) {

            fps.Update();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (std::round(fps.GetFPS()) != 5.f)
            throw std::runtime_error("FRAMES PER SECOND DOES NOT MATCH! 200ms");

        fps.Update(true);
        for (int i = 0; i < 30; i++) {

            fps.Update();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        if (std::round(fps.GetFPS()) != 3.f)
            throw std::runtime_error("FRAMES PER SECOND DOES NOT MATCH! 300ms");

        fps.Update(true);
        for (int i = 0; i < 10; i++) {

            fps.Update();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        if (std::round(fps.GetFPS()) != 2.f)
            throw std::runtime_error("FRAMES PER SECOND DOES NOT MATCH! 500ms");
    }
    catch (std::exception& e) {
        return { -1, e };
    }
    

    return { 0, no_exception() };
}
