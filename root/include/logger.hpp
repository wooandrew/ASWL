// ASWL | logger.hpp :: Andrew Woo, 2019-2020

#pragma once

#ifndef ASWL_UTILITIES_LOGGER
#define ASWL_UTILITIES_LOGGER

#include "utilities.hpp"

#include <fstream>
#include <streambuf>

namespace ASWL::utilities {

	// Uninstantiated loggers
	template<typename T> void _uLogger(T override, bool useDateTime = false) {

		std::lock_guard<std::mutex> lock(mu);

		if (useDateTime)
			std::cerr << GetDateTime() << " |     | " << override << std::endl;
		else
			std::cerr << override;
	}
	template<typename ERRCODE, typename ERRMSG> void _uLogger(ERRCODE errorCode, ERRMSG errorMessage) {

		std::lock_guard<std::mutex> lock(mu);
		std::cerr << GetDateTime() << " |" << errorCode << "| " << errorMessage << std::endl;
	}
	template<typename ERRCODE, typename...ERRMSG> void _uLogger(ERRCODE errorCode, ERRMSG...errorMessage) {

		std::lock_guard<std::mutex> lock(mu);
		std::cerr << GetDateTime() << " |" << errorCode << "| " << VariadicAdd(errorMessage...) << std::endl;
	}

	template<typename T> void _uLogger(std::ostream& __stream, T override, bool useDateTime = false) {

		std::lock_guard<std::mutex> lock(mu);

		if (useDateTime)
			__stream << GetDateTime() << " |     | " << override << std::endl;
		else
			__stream << override;
	}
	template<typename ERRCODE, typename ERRMSG> void _uLogger(std::ostream& __stream, ERRCODE errorCode, ERRMSG errorMessage) {

		std::lock_guard<std::mutex> lock(mu);
		__stream << GetDateTime() << " |" << errorCode << "| " << errorMessage << std::endl;
	}
	template<typename ERRCODE, typename...ERRMSG> void _uLogger(std::ostream& __stream, ERRCODE errorCode, ERRMSG...errorMessage) {
		std::lock_guard<std::mutex> lock(mu);
		__stream << GetDateTime() << " |" << errorCode << "| " << VariadicAdd(errorMessage...) << std::endl;
	}

	// Instanced logger
	class Logger {

	public:

		Logger();
		Logger(std::streambuf* _stream);

		void SetStream(std::streambuf* _stream);

		template <typename T> void log(T override, bool useDateTime = false) {
			if (__Logger == __Logger_::ENABLED)
				_uLogger(__log, override, useDateTime);
		}

		template <typename ERRCODE, typename...ERRMSG> void log(ERRCODE errorCode, ERRMSG...errorMessage) {
			if (__Logger == __Logger_::ENABLED)
				_uLogger(__log, errorCode, errorMessage...);
		}

		enum class __Logger_ {
			ENABLED,
			DISABLED
		}; __Logger_ __Logger;

	private:
		std::ostream __log;
	};

}

#endif // !ASWL_UTILITIES_LOGGER
