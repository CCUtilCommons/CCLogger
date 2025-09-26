#pragma once
#include "decorator.h"
#include "logger_level.h"
#include <memory>

namespace Clog {

class ConsoleColorDecorator : public LoggerDecorator {
public:
	ConsoleColorDecorator(std::unique_ptr<LoggerDecorator> log = nullptr)
	    : LoggerDecorator(std::move(log)) { }

	std::string make_decorate(const std::string& formatted, const CCLoggerLevel level) override;
	std::string make_decorate(std::string&& formatted, const CCLoggerLevel level) override;
};

}
