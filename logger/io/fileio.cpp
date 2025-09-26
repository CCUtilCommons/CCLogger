#include "fileio.h"
#include <string>
using namespace Clog;

FileLoggerIO::FileLoggerIO(const std::string& filepath)
    : file_path_(filepath) {
	file_stream_.open(filepath, std::ios::out | std::ios::app);
}

FileLoggerIO::~FileLoggerIO() {
	flush();
	if (file_stream_.is_open()) {
		file_stream_.close();
	}
}

bool FileLoggerIO::write_logger(const std::string& log_info) {
	std::lock_guard<std::mutex> lock(file_mutex_);

	if (file_stream_.is_open()) {
		file_stream_ << log_info << '\n';
		return true;
	}
	return false;
}

bool FileLoggerIO::flush() {
	std::lock_guard<std::mutex> lock(file_mutex_);
	if (file_stream_.is_open()) {
		file_stream_.flush();
		return !file_stream_.fail();
	}
	return false;
}