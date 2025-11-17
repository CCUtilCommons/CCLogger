#pragma once
#include "CCLoggerExports.h"
#include "CCSourceLocation.h"
#include "formater.h"
#include "formater/blank_formater.h"
#include "logger_io.h"
#include "logger_level.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace CCThreadPool {
class CCThreadPool;
}; // Anouncements

namespace Clog {

struct CCLOG_API ThreadPoolDeleter {
	void operator()(CCThreadPool::CCThreadPool* ptr) const;
};

class CCLOG_API CCLogger {
public:
	CCLogger();
	CCLogger(
	    std::unique_ptr<LoggerFormatter> formater,
	    std::unique_ptr<LoggerIO> default_io);
	~CCLogger();
#if __cplusplus >= 202002L
	void log(const std::string& msg,
	         const CCLoggerLevel level,
	         std::source_location loc = std::source_location::current());
	void log(std::string&& msg,
	         const CCLoggerLevel level,
	         std::source_location loc = std::source_location::current());
#endif
	void log(const std::string& msg,
	         const CCLoggerLevel level,
	         const CCSourceLocation& loc);
	void log(std::string&& msg,
	         const CCLoggerLevel level,
	         const CCSourceLocation& loc);
	void registerIOBackEnd(std::unique_ptr<LoggerIO> backend,
	                       std::unique_ptr<LoggerFormatter> formater = std::make_unique<BlankFormater>());
	bool removeIOBackEnd(LoggerIO* backend);

	bool defBackendSilent() const { return silent_defbackend; }
	void setDefBackendSilent(bool b) { silent_defbackend = b; }

private:
	std::unique_ptr<LoggerFormatter> formater; ///< formater
	std::unique_ptr<LoggerIO> default_io; ///< default IO

	std::mutex io_manager_locker;

	std::unordered_map<std::unique_ptr<LoggerIO>,
	                   std::unique_ptr<LoggerFormatter>>
	    broadcast_io;
	std::unique_ptr<CCThreadPool::CCThreadPool, ThreadPoolDeleter> log_worker_pool;
	std::atomic<bool> silent_defbackend { false };

private:
#if __cplusplus >= 202002L
	/* ------------ Helpers ------------*/
	void log_direct(const std::string& msg,
	                const CCLoggerLevel level,
	                std::source_location loc = std::source_location());

	void log_direct(std::string&& msg,
	                const CCLoggerLevel level,
	                std::source_location loc = std::source_location());
#endif

	void log_direct(const std::string& msg,
	                const CCLoggerLevel level,
	                const CCSourceLocation& loc);
	void log_direct(std::string&& msg,
	                const CCLoggerLevel level,
	                const CCSourceLocation& loc);
	/* ------------ Disable default functors ------------*/
	CCLogger(const CCLogger&) = delete;
	CCLogger& operator=(const CCLogger&) = delete;
	CCLogger(const CCLogger&&) = delete;
	CCLogger& operator=(const CCLogger&&) = delete;
};

}
