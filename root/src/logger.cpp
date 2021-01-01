// ASWL | logger.cpp :: Andrew Woo, 2019-2020

#include "logger.hpp"

namespace ASWL::utilities {

    Logger::Logger() : __log(std::cerr.rdbuf()) {
        __Logger = __Logger_::ENABLED;
    }

    Logger::Logger(std::streambuf* _stream) : __log(_stream) {
        __Logger = __Logger_::ENABLED;
    }

    void Logger::SetStream(std::streambuf* _stream) {
        __log.rdbuf(_stream);
    }
}
