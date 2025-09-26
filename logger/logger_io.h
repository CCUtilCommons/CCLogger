#pragma once
#include <string>

namespace Clog {
/**
 * @brief   Logger IO Cares about where to write
 *          by given formatted strings
 *
 */
class LoggerIO {
public:
	virtual ~LoggerIO() = default;
	/**
	 * @brief   process_enable_io will starts the IO Sessions,
	 *          Logger will call enable_io when it is the first time
	 *          to write IO
	 *
	 * @return true
	 * @return false
	 */
	virtual bool process_enable_io() = 0;
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

	/**
	 * @brief   followings are LoggerIO OK, when io_enabled
	 *          we think the IO is ready
	 */
	bool getIOEnabled() const { return io_enabled; }
	void setIOEnabled(const bool io_enabled) { this->io_enabled = io_enabled; }

protected:
	bool io_enabled { false };
};

}
