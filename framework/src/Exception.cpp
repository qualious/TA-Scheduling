/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include <iostream>
#include <string>
#include <sstream>

#include "../headers/Exception.h"
#include "../headers/Logger.h"

Exception::Exception(const std::string where, const std::string& message) : msg{message} {
    std::ostringstream msg;
    msg << "Exception happened at: ";
    msg << where << std::endl;
    msg << "Message was: " << std::endl;
    msg << message.c_str() << std::endl;
    Logger& logger = Logger::instance();
    logger.error(msg.str());
}

Exception::~Exception() { }

std::string
Exception::what() const { return msg; }
