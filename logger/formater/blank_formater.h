#pragma once
#include "CCLoggerExports.h"
#include "formater.h"

namespace Clog {

class CCLOG_API BlankFormater : public LoggerFormatter {
public:
	BlankFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter> decorator = nullptr)
	    : LoggerFormatter(std::move(decorator)) { }
#if __cplusplus >= 202002L
	/**
	 * @brief format the context string
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	std::string format(
	    const std::string& msg, const CCLoggerLevel level,
	    const std::source_location& context_info) override;

	/**
	 * @brief format the context string (with move assignments)
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	std::string format(
	    std::string&& msg, const CCLoggerLevel level,
	    const std::source_location& context_info) override;
#endif
	/**
	 * @brief format the context string
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	std::string format(
	    const std::string& msg, const CCLoggerLevel level,
	    const CCSourceLocation& context_info) override;

	/**
	 * @brief format the context string (with move assignments)
	 *
	 * @param msg
	 * @param level
	 * @param context_info
	 * @return std::string
	 */
	std::string format(
	    std::string&& msg, const CCLoggerLevel level,
	    const CCSourceLocation& context_info) override;
};

}