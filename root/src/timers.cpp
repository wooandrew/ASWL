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

#include <ASWL/aswl.hpp>
#include <ASWL/timers.hpp>
#include <ASWL/logger.hpp>

#include <iostream>

namespace ASWL::Timers {

	ElapsedTime::ElapsedTime() {
		hrClock = {};
		_start = hrClock.now();
		stopped = true;
	}

	void ElapsedTime::start() {

		stopped = false;
		_start = hrClock.now();
	}

	float ElapsedTime::now() {

		if (stopped)
			throw time_exception("Timer is stopped! Call start()!");

		return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(hrClock.now() - _start).count() / 1000;
	}

	float ElapsedTime::lap() {

		if (stopped)
			throw time_exception("Timer is stopped! Call start()!");

		auto ret = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(hrClock.now() - _start).count() / 1000;
		_start = hrClock.now();

		return ret;
	}

	void ElapsedTime::stop() {
		stopped = true;
	}

	DeltaTime::DeltaTime() {

		hrClock = {};

		start = hrClock.now();

		deltaTime = 0;
		lastTime = 0;
	}

	double DeltaTime::GetDeltaTime() {
		return deltaTime;
	}

	void DeltaTime::UpdateDeltaTime(bool reset) {

		if (reset) {
			start = hrClock.now();
			return;
		}

		stop = hrClock.now();

		deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(stop - start).count() / 1000;

		start = stop;
	}

	FramesPerSecond::FramesPerSecond() {

		FPS = 0;
		frames_passed = 0;

		hrClock = {};

		start = hrClock.now();
	}

	const double FramesPerSecond::GetFT() const {
		return 1000.f / FPS;
	}
	const double FramesPerSecond::GetFPS() const {
		return FPS;
	}

	void FramesPerSecond::Update(bool reset) {

		if (reset) {
			start = hrClock.now();
			return;
		}	

		stop = hrClock.now();

		std::chrono::duration<double> elapsed_time = stop - start;

		frames_passed++;

		if (elapsed_time.count() > 0.25) {
			FPS = frames_passed / elapsed_time.count();
			start = hrClock.now();
			frames_passed = 0;
		}
	}

	// operator<< overloads
	std::ostream& operator<<(std::ostream& _stream, const FramesPerSecond& _fps) {
		
		_stream << _fps.FPS;
		return _stream;
	}
}
