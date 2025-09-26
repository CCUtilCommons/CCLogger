#pragma once
#include "logger_level.h"
#include <memory>
#include <string>
namespace Clog {
class LoggerDecorator {
public:
	virtual ~LoggerDecorator() = default;
	LoggerDecorator(std::unique_ptr<LoggerDecorator> next = nullptr)
	    : next_decorator(std::move(next)) {
	}
	/**
	 * @brief For outer interface, we should always call the
	 *        run_decorate
	 *
	 * @param formatted
	 * @return std::string
	 */
	std::string run_decorate(const std::string& formatted, const CCLoggerLevel logger_level) {
		auto this_decorate = make_decorate(formatted, logger_level);
		return next_decorator ? next_decorator->run_decorate(this_decorate, logger_level) : this_decorate;
	}

	std::string run_decorate(std::string&& formatted, const CCLoggerLevel logger_level) {
		auto this_decorate = make_decorate(std::move(formatted), logger_level);
		return next_decorator ? next_decorator->run_decorate(std::move(this_decorate), logger_level) : this_decorate;
	}

	/**
	 * @brief   User should rewrite the make_decorate to foucs the
	 *          logic of decorations
	 *
	 * @param formatted
	 * @return std::string
	 */
	virtual std::string make_decorate(const std::string& formatted, const CCLoggerLevel logger_level)
	    = 0;
	/**
	 * @brief   User should rewrite the make_decorate to foucs the
	 *          logic of decorations
	 *
	 * @param formatted
	 * @return std::string
	 */
	virtual std::string make_decorate(std::string&& formatted, const CCLoggerLevel logger_level) = 0;

private:
	std::unique_ptr<LoggerDecorator> next_decorator;
};

}
