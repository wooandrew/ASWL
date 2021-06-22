// ASWL (c) 2021 Andrew Woo
// Website: https://wooandrew.dev https://wooandrew.github.io
// Email: seungminleader@gmail.com

/* MIT License
 *
 * Copyright (c) 2021 Andrew Woo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#pragma once

#ifndef ASWL_LOGGER
#define ASWL_LOGGER

#include <iostream>
#include <utility>
#include <fstream>
#include <mutex>

#include "utilities.hpp"

namespace ASWL::Logger {

    namespace {

        // Holds instance of std::clog
        static std::streambuf* stream_buffer_clog_default__ = std::clog.rdbuf();
        static std::streambuf* stream_buffer_current__ = stream_buffer_clog_default__;
    }

    void SetLogStream();
    void SetLogStream(std::fstream& file);

    template <typename ... MSGS>
    void logger(bool _endLine, MSGS&& ... _msgs) {

        if (_endLine) {
            ((std::clog << std::forward<MSGS>(_msgs) << ' '), ...) << std::endl;
        }
    }

    template<typename ERRNUM, typename ... ERRMSG> 
    void logger(ERRNUM _num, ERRMSG&& ... _msgs) {

        std::lock_guard<std::mutex> lock(ASWL::Utilities::mu);
        std::clog << ASWL::Utilities::GetDateTime() << " |" << _num << '|';
        ((std::clog << ' ' << std::forward<ERRMSG>(_msgs)), ...) << std::endl;
    }
}

#endif // !ASWL_LOGGER
