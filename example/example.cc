#include "CCLogger.hpp"
#include "logger_level.h"
#include <string>
using namespace Clog;
int main() {
	CCLogger logger;
	logger.log("Welp, I gonna trace these", CCLoggerLevel::Trace);
	logger.log("Hello, logging world!", CCLoggerLevel::Info);
	logger.log("Something debug", CCLoggerLevel::Debug);
	logger.log(std::string("Error occurred: code=123"), CCLoggerLevel::Error);

	std::string msg = "A warning: low memory";
	logger.log(std::move(msg), CCLoggerLevel::Warning);

	return 0;
}
