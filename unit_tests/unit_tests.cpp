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

#include <iostream>

#define ASWL_SILENCED
#include <ASWL/aswl.hpp>

#include "tests/test.hpp"
#include "tests/test_timers.hpp"

int ParseReturn(std::pair<int, std::exception> _pair) {

    if (_pair.first)
        std::clog << "\tFAILURE\t\tEXCEPTION: " << _pair.second.what() << std::endl;
    else
        std::clog << "\tSUCCESS" << std::endl;

    return std::abs( _pair.first);
}

int main(int argc, char* argv[]) {

    int fails = 0;

    fails += ParseReturn(TestET());
    fails += ParseReturn(TestDT());
    fails += ParseReturn(TestFPS());

    return fails;
}
