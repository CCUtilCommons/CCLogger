#pragma once
#include "CCLoggerExports.h"
#include "decorator.h"
#include "logger_level.h"
#include <memory>
namespace Clog {

class CCLOG_API ConsoleColorDecorator : public LoggerDecorator {
public:
	ConsoleColorDecorator(std::unique_ptr<LoggerDecorator> log = nullptr)
	    : LoggerDecorator(std::move(log)) { }

	std::string make_decorate(const std::string& formatted, const CCLoggerLevel level) override;
	std::string make_decorate(std::string&& formatted, const CCLoggerLevel level) override;
};

}
