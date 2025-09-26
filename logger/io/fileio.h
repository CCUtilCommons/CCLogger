#pragma once
#include "logger_io.h"
#include <fstream>
#include <mutex>
#include <string>

namespace Clog {
class FileLoggerIO : public LoggerIO {
public:
	FileLoggerIO(const std::string& filepath);
	~FileLoggerIO() override;
	bool write_logger(const std::string& log_info) override;
	bool flush() override;

private:
	std::string file_path_;
	std::ofstream file_stream_;
	std::mutex file_mutex_;

	FileLoggerIO(const FileLoggerIO&) = delete;
	FileLoggerIO& operator=(const FileLoggerIO&) = delete;
};

}
