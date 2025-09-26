#pragma once
#include "logger_io.h"

/**
 * @brief Null IO Do nothing, thats the case lol
 *
 */
class NullIO : public Clog::LoggerIO {
	bool write_logger(const std::string& log_info) override { return true; };
	bool flush() override { return true; };
};