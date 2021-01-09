// ASWL (c) 2021 Andrew Woo
// Website: https://wooandrew.tech https://wooandrew.github.io
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

#ifndef ASWL_UTILITIES
#define ASWL_UTILITIES

#include <string>
#include <vector>
#include <chrono>
#include <mutex>

namespace ASWL::Utilities {

	extern bool silenced;
	extern std::mutex mu;

	std::string GetDateTime(const std::string& format = "%Y/%m/%d _ %T");

	template<typename T> T VariadicAdd(T value) {
		return value;
	}
	template<typename T, typename...Args> T VariadicAdd(T value, Args ... args) {
		return value + VariadicAdd<T>(args...);
	}

	std::vector<std::string> split(const std::string& _input, char delimiter = ' ');

	struct FramesPerSecond {

		// Something is wrong with this utility. I think. I can't be sure.

		FramesPerSecond() = delete;

		static double GetFPS();
		static void UpdateFPS(bool reset = false);

	private:
		static double FPS;
		static int framesPassed;
		static bool firstCall;
	};

	struct DeltaTime {

		DeltaTime();

		double GetDeltaTime();
		void UpdateDeltaTime(bool reset = false);

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> stop;

		double deltaTime;
		double lastTime;

		bool firstCall;
	};
}

#endif // !ASWL_UTILITIES
