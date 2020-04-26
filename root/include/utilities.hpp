// ASWL | utilities.hpp :: Andrew Woo, 2019-2020

#pragma once

#ifndef UTILITIES_NAMESPACE
#define UTILITIES_NAMESPACE

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <mutex>
#include <ctime>

namespace ASWL {

	namespace utilities {

		namespace { // "private" namespace members. These values cannot be accessed outside of the definitions.

			static bool silenced = false;

			static std::mutex mu;

			static std::streambuf* stream_buffer_cout_default__ = std::cout.rdbuf();
			static std::streambuf* stream_buffer_cerr_default__ = std::cerr.rdbuf();
			static std::streambuf* stream_buffer_cin_default__ = std::cin.rdbuf();
		}

		void SilenceWarnings();

		void RedirectIOStream(std::fstream& file, int stream, bool reset = false);

		std::string GetDateTime(std::string format = "%Y/%m/%d _ %T");

		template<typename T> T VariadicAdd(T value) {
			return value;
		}
		template<typename T, typename...Args> T VariadicAdd(T value, Args...args) {
			return value + VariadicAdd<T>(args...);
		}

		template<typename T> void Logger(T override, bool useDateTime = false) {

			std::lock_guard<std::mutex> lock(mu);

			if (useDateTime)
				std::cerr << GetDateTime() << " |     | " << override << std::endl;
			else
				std::cerr << override;
		}
		template<typename ERRNUM, typename ERRMSG> void Logger(ERRNUM errorNumber, ERRMSG errorMessage) {

			std::lock_guard<std::mutex> lock(mu);
			std::cerr << GetDateTime() << " |" << errorNumber << "| " << errorMessage << std::endl;
		}
		template<typename ERRNUM, typename...ERRMSG> void Logger(ERRNUM errorNumber, ERRMSG...errorMessage) {

			std::lock_guard<std::mutex> lock(mu);

			std::cerr << GetDateTime() << " |" << errorNumber << "| " << VariadicAdd(errorMessage...) << std::endl;
		}

		std::vector<std::string> split(std::string input, char delimiter = ' ');

		struct DeltaTime {

			DeltaTime();

			double GetDeltaTime();
			void UpdateDeltaTime(bool reset = false);

		private:

			std::chrono::time_point<std::chrono::steady_clock> start;
			std::chrono::time_point<std::chrono::steady_clock> stop;

			double deltaTime;
			double lastTime;

			bool firstCall;
		};

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

		template<typename T> struct Dimensions2D {
			T width;
			T height;
		};
		template<typename T> Dimensions2D<T> make_2d_dimension(T width, T height) {

			Dimensions2D<T> ret;
			ret.width = width;
			ret.height = height;

			return ret;
		}
	}
}

namespace util = ASWL::utilities; // Deprecated renaming of "utilities" namespace. It should be replaced by the individual user.
namespace misc = ASWL::utilities; // Deprecated renaming of "utilities" namespace. It should be replaced by the individual user.

#endif // !UTILITIES_NAMESPACE
