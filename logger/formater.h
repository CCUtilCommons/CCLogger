#pragma once
#include "CCLoggerExports.h"
#include "CCSourceLocation.h"
#include "logger_level.h"
#include <memory>
#include <string>

namespace Clog {

class LoggerDecorator;
struct CCLOG_API LoggerDecoratorDeleter {
	void operator()(LoggerDecorator* ptr) const;
};

class CCLOG_API LoggerFormatter {
public:
	virtual ~LoggerFormatter();
	LoggerFormatter(std::unique_ptr<
	                    LoggerDecorator, LoggerDecoratorDeleter>
	                    next_one
	                = nullptr);
#if __cplusplus >= 202002L
	/**
	 * @brief format the context string
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	virtual std::string format(
	    const std::string& msg, const CCLoggerLevel level,
	    const std::source_location& context_info)
	    = 0;

	/**
	 * @brief format the context string (with move assignments)
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	virtual std::string format(
	    std::string&& msg, const CCLoggerLevel level,
	    const std::source_location& context_info)
	    = 0;
#endif
	/**
	 * @brief format the context string
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	virtual std::string format(
	    const std::string& msg, const CCLoggerLevel level,
	    const CCSourceLocation& context_info)
	    = 0;

	/**
	 * @brief format the context string (with move assignments)
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	virtual std::string format(
	    std::string&& msg, const CCLoggerLevel level,
	    const CCSourceLocation& context_info)
	    = 0;

protected:
	std::string run_decorate(const std::string& after_decorate, const CCLoggerLevel level);
	std::string run_decorate(std::string&& after_decorate, const CCLoggerLevel level);
	std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter> next_decorator;
};

}
