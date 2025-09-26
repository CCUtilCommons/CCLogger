#pragma once
#include "formater.h"
#include "logger_io.h"
#include "logger_level.h"
#include <memory>
#include <mutex>
#include <source_location>
#include <vector>

namespace Clog {

class CCLogger {
public:
	CCLogger();
	CCLogger(
	    std::unique_ptr<LoggerFormatter> formater,
	    std::unique_ptr<LoggerIO> default_io);

	void log(const std::string& msg,
	         const CCLoggerLevel level,
	         std::source_location loc = std::source_location::current());
	void log(std::string&& msg,
	         const CCLoggerLevel level,
	         std::source_location loc = std::source_location::current());

	void registerIOBackEnd(std::unique_ptr<LoggerIO> backend);
	bool removeIOBackEnd(LoggerIO* backend);

private:
	std::unique_ptr<LoggerFormatter> formater; ///< formater
	std::unique_ptr<LoggerIO> default_io; ///< default IO

	std::mutex io_manager_locker;
	std::vector<std::unique_ptr<LoggerIO>> broadcast_io;

private:
	/* ------------ Helpers ------------*/
	void log_direct(const std::string& msg,
	                const CCLoggerLevel level,
	                std::source_location loc = std::source_location());

	void log_direct(std::string&& msg,
	                const CCLoggerLevel level,
	                std::source_location loc = std::source_location());

	/* ------------ Disable default functors ------------*/
	CCLogger(const CCLogger&) = delete;
	CCLogger& operator=(const CCLogger&) = delete;
	CCLogger(const CCLogger&&) = delete;
	CCLogger& operator=(const CCLogger&&) = delete;
};

}
