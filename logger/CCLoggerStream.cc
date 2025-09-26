#include "CCLoggerStream.h"
using namespace Clog;

LoggerStream& LoggerStream::operator<<(std::ostream& (*manip)(std::ostream&)) {
	if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
		flush();
	} else {
		manip(buffer);
	}
	return *this;
}

void LoggerStream::flush() {
	std::lock_guard<std::mutex> lock(mtx);
	logger->log(buffer.str(), level);
	buffer.str("");
	buffer.clear();
}