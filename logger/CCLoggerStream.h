#pragma once
#include "logger_level.h"
#include <memory>
#pragma once
#include "CCLogger.hpp"
#include <mutex>
#include <sstream>

namespace Clog {

class LoggerStream {
public:
	LoggerStream(
	    CCLoggerLevel level = CCLoggerLevel::Info,
	    // default we calls the def backends and formats, so you need to
	    // switch the cclogger_default_behave.cc to modify the sessions
	    std::unique_ptr<CCLogger> logger = std::make_unique<CCLogger>())
	    : level(level)
	    , logger(std::move(logger)) { }

	/**
	 * @brief   Bonus here: If you need flush, you need to invoke
	 *          by pushing into std::endl for a flush
	 *
	 * @tparam T
	 * @param value
	 * @return LoggerStream&
	 */
	template <typename T>
	LoggerStream& operator<<(const T& value) {
		buffer << value;
		if (buffer.str().size() > 1024) {
			flush();
		}
		return *this;
	}

	LoggerStream& operator<<(std::ostream& (*manip)(std::ostream&));
	void flush();
	CCLogger& getLogger() { return *logger; }
	void setLevel(CCLoggerLevel lvl) { level = lvl; }

private:
	std::unique_ptr<CCLogger> logger;
	CCLoggerLevel level;
	std::ostringstream buffer;
	std::mutex mtx;
};

inline LoggerStream trace(CCLoggerLevel::Trace);
inline LoggerStream debug(CCLoggerLevel::Debug);
inline LoggerStream info(CCLoggerLevel::Info);
inline LoggerStream warn(CCLoggerLevel::Warning);
inline LoggerStream error(CCLoggerLevel::Error);

} // namespace Clog
