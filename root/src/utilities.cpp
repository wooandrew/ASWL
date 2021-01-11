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

#include "ASWL/utilities.hpp"

#include <iostream>

#include <ctime>
#include <sstream>
#include <fstream>

#include "ASWL/logger.hpp"

namespace ASWL::Utilities {

	bool silenced = false;
	std::mutex mu;

	std::string GetDateTime(const std::string& format) {

		auto timeNow = std::chrono::system_clock::now();
		time_t timeNow_t = std::chrono::system_clock::to_time_t(timeNow);

		std::ostringstream oss;

		if (format == "ctd")
			oss << std::ctime(&timeNow_t);
		else
			oss << std::put_time(std::localtime(&timeNow_t), format.c_str());

		return oss.str();
	}

	std::string ReadFile(const std::string& _path, std::ios::openmode _openmode) {

		std::string data = "";

		std::ifstream input(_path, _openmode);
		if (input) {

			input.seekg(0, std::ios::end);
			data.resize(input.tellg());

			input.seekg(0, std::ios::beg);
			input.read(&data[0], data.size());
			input.close();
		}
		else
			Logger::logger("     ", "Error reading file at ", _path);

		return data;
	}

	std::vector<std::string> split(const std::string& _input, char delimiter) {

		std::vector<std::string> ret;

		std::istringstream iss(_input);
		std::string token;

		while (std::getline(iss, token, delimiter))
			ret.push_back(token);

		return ret;
	}

	double FramesPerSecond::FPS = 0;
	int FramesPerSecond::framesPassed = 0;
	bool FramesPerSecond::firstCall = false;

	double FramesPerSecond::GetFPS() {
		return FPS;
	}

	void FramesPerSecond::UpdateFPS(bool reset) {

		static std::chrono::high_resolution_clock dtimer;

		static auto start = dtimer.now();
		static auto stop = dtimer.now();

		if (firstCall || reset) {
			stop = dtimer.now();
			start = dtimer.now();
			firstCall = false;
		}
		else
			stop = dtimer.now();


		std::chrono::duration<double> elapsed_time = stop - start;

		framesPassed++;

		if (elapsed_time.count() > 0.25) {
			FPS = framesPassed / elapsed_time.count();
			start = dtimer.now();
			framesPassed = 0;
		}
	}

	DeltaTime::DeltaTime() {

		// WARNING -> DeltaTime functions have not been tested for accuracy!

		std::chrono::high_resolution_clock dtimer;

		if (!silenced)
			std::clog << "WARNING -> DeltaTime functions have not been tested for accuracy!" << std::endl;

		start = dtimer.now();
		stop = dtimer.now();

		deltaTime = 0;
		lastTime = 0;
		firstCall = true;
	}

	double DeltaTime::GetDeltaTime() { // WARNING -> DeltaTime functions have not been tested for accuracy!
		return deltaTime;
	}

	void DeltaTime::UpdateDeltaTime(bool reset) { // WARNING -> DeltaTime functions have not been tested for accuracy!

		std::chrono::high_resolution_clock dtimer;

		if (firstCall || reset) {
			start = dtimer.now();
			firstCall = false;
		}

		stop = dtimer.now();

		deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(stop - start).count() / 1000;

		start = stop;
	}
}