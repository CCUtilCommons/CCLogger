#include "CCLogger.hpp"
#include "io/fileio.h"
#include <memory>

int main() {
	using namespace Clog;

	CCLogger logger;

	// 添加文件输出
	logger.registerIOBackEnd(std::make_unique<FileLoggerIO>("log.txt"));

#if __cplusplus > 202002L
	logger.log("This is an info message", CCLoggerLevel::Info);
	logger.log("This is a warning message", CCLoggerLevel::Warning);
	logger.log("This is an error message", CCLoggerLevel::Error);
#else
	logger.log("This is an info message", CCLoggerLevel::Info, PLACE_LOC);
	logger.log("This is a warning message", CCLoggerLevel::Warning, PLACE_LOC);
	logger.log("This is an error message", CCLoggerLevel::Error, PLACE_LOC);
#endif

	return 0;
}
