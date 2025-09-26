#pragma once
#include "logger_io.h"

/**
 * @brief   StandardConsoleIO is such a class that do the real write
 *          to the console standard,
 * @note    write_logger wont flush the console, call flush to flush everything
 *
 */
class StandardConsoleIO : public Clog::LoggerIO {
	bool write_logger(const std::string& log_info) override;
	bool flush() override;
};
