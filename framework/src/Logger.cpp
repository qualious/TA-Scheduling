/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include <iostream>
#include <sstream>
#include "../headers/Logger.h"

Logger* Logger::_instance = 0;
std::ofstream Logger::_file("project.log", std::ios::out|std::ios::trunc);

Logger::Logger() { };

Logger::~Logger() { _file.close(); }

Logger& Logger::instance() throw () {
    if (_instance == 0) {
        _instance = new Logger();
    }
    return *_instance;
}

void
Logger::trace(LOGGER_LEVEL level, std::string message) {
    if (level == LOGGER_NONE) {
        std::ostringstream msg;
        msg << "Misaligned usage of Logger with level=NONE\n";
        msg << "Message was:\n";
        msg << message.c_str();
        Logger::error(msg.str());
    }
    log(level, message);
}

void
Logger::debug(std::string message) {
    Logger::log(LOGGER_DEBUG, message);
}

void
Logger::info(std::string message) {
    Logger::log(LOGGER_INFO, message);
}

void
Logger::warning(std::string message) {
    Logger::log(LOGGER_WARNING, message);
}

void
Logger::error(std::string message) {
    Logger::log(LOGGER_ERROR, message);
}

void
Logger::log(LOGGER_LEVEL level, std::string message) {
    if (_file.is_open())
        _file << indicators.at(level) << " : " << message << std::endl;
    else
        std::cout << indicators.at(level) << " : " << message << std::endl;
}
