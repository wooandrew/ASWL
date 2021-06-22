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

#ifndef ASWL_TIMERS
#define ASWL_TIMERS

#include <chrono>
#include <ostream>
#include <exception>

namespace ASWL::Timers {

	class time_exception : public std::exception {
	public:
		time_exception(const char* _str) : std::exception(_str) {};
	};

	class ElapsedTime {

	public:

		ElapsedTime();

		void start();
		float now();
		float lap();
		void stop();

	private:

		std::chrono::high_resolution_clock hrClock;
		std::chrono::time_point<std::chrono::high_resolution_clock> _start;
		bool stopped;
	};

	class DeltaTime {

	public:

		DeltaTime();

		double GetDeltaTime();
		void UpdateDeltaTime(bool reset = false);

	private:

		std::chrono::high_resolution_clock hrClock;

		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> stop;

		double deltaTime;
		double lastTime;
	};

	class FramesPerSecond {

		// Something is wrong with this utility. I think. I can't be sure.

	public:

		FramesPerSecond();

		const double GetFT() const; // Untested
		const double GetFPS() const;
		void Update(bool reset = false);

		friend std::ostream& operator<<(std::ostream& _stream, const FramesPerSecond& _fps);

	private:

		std::chrono::high_resolution_clock hrClock;
		
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> stop;

		double FPS;
		int frames_passed;
	};
}

#endif // !ASWL_TIMERS
