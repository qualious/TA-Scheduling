/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <fstream>

typedef enum LOGGER_LEVEL_ENUM
{
	LOGGER_NONE = 0,
	LOGGER_DEBUG,
	LOGGER_INFO,
	LOGGER_WARNING,
	LOGGER_ERROR
} LOGGER_LEVEL;

const auto indicators = std::vector<std::string>{ "NONE", "DEBUG", "INFO", "WARNING", "ERROR" };

class Logger {
public:
    static Logger& instance() throw ();
	static void debug(std::string);
	static void info(std::string);
	static void warning(std::string);
	static void error(std::string);
	static void trace(LOGGER_LEVEL level, std::string);
protected:
	Logger();
	~Logger();
private:
    static Logger* _instance;
    static std::ofstream _file;
	static void log(LOGGER_LEVEL, std::string);
};

#endif // LOGGER
