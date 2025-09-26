#pragma once
#include "logger_io.h"

/**
 * @brief   StandardConsoleIO is such a class that do the real write
 *          to the console standard,
 * @note    write_logger wont flush the console, call flush to flush everything
 *
 */
class StandardConsoleIO : public Clog::LoggerIO {
	// console IO no need to be ready
	bool process_enable_io() override { return true; }
	bool write_logger(const std::string& log_info) override;
	bool flush() override;
};
