// ASWL | utilities.cpp :: Andrew Woo, 2019-2020

#include "utilities.hpp"

namespace ASWL::utilities {

	void SilenceWarnings() {
		silenced = !silenced;
	}

	void RedirectIOStream(std::fstream& file, int stream, bool reset) {

		std::lock_guard<std::mutex> lock(mu);

		if (reset) {
			std::cout.rdbuf(stream_buffer_cout_default__);
			std::cerr.rdbuf(stream_buffer_cerr_default__);
			std::cin.rdbuf(stream_buffer_cin_default__);
		}
		else {

			if (stream == 0)
				std::cout.rdbuf(file.rdbuf());
			else if (stream == 1)
				std::cerr.rdbuf(file.rdbuf());
			else if (stream == 2)
				std::cin.rdbuf(file.rdbuf());
			else {

				std::cerr << "Error: Unknown stream value [" << stream << "]. Ignoring redirect call." << std::endl;

				if(std::cerr.rdbuf() != stream_buffer_cerr_default__) {

					std::streambuf* tempStreamBuf = std::cerr.rdbuf();

					std::cerr.rdbuf(stream_buffer_cerr_default__);
					std::cerr << "Error: Unknown stream value [" << stream << "]. Ignoring redirect call." << std::endl;
					std::cerr.rdbuf(tempStreamBuf);
				}
			}
		}
	}
	
	std::string GetDateTime(std::string format) {

		auto timeNow = std::chrono::system_clock::now();
		time_t timeNow_t = std::chrono::system_clock::to_time_t(timeNow);

		std::ostringstream oss;

		if (format == "ctd")
			oss << std::ctime(&timeNow_t);
		else 
			oss << std::put_time(std::localtime(&timeNow_t), format.c_str());

		return oss.str();
	}

	std::vector<std::string> utilities::split(std::string input, char delimiter) {

		std::vector<std::string> ret;
		std::ostringstream oss;
		oss << input;

		std::istringstream iss(oss.str());
		std::string token;

		while (std::getline(iss, token, delimiter))
			ret.push_back(token);

		return ret;
	}

	DeltaTime::DeltaTime() {

		// WARNING -> DeltaTime functions have not been tested for accuracy!

		std::chrono::high_resolution_clock dtimer;

		if(!silenced)
			std::cerr << "WARNING -> DeltaTime functions have not been tested for accuracy!" << std::endl;

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
}