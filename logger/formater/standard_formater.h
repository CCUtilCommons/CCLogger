#pragma once
#include "decorator.h"
#include "formater.h"
#include "logger_level.h"
#include <memory>

namespace Clog {

class StandardFormater : public LoggerFormatter {
public:
	~StandardFormater() override = default;
	StandardFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter> decorator)
	    : LoggerFormatter(std::move(decorator)) { }
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
};

}
