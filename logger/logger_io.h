#pragma once
#include "CCLoggerExports.h"
#include <string>

namespace Clog {
/**
 * @brief   Logger IO Cares about where to write
 *          by given formatted strings
 *
 */
class CCLOG_API LoggerIO {
public:
	virtual ~LoggerIO() = default;
	/**
	 * @brief Interface of write logger
	 *
	 * @param log_info
	 * @return true
	 * @return false
	 */
	virtual bool write_logger(const std::string& log_info) = 0;

	/**
	 * @brief Interface of flush a logger
	 *
	 * @return true
	 * @return false
	 */
	virtual bool flush() = 0;
};

}
