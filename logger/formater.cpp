#include "formater.h"
#include "decorator.h"
#include "logger_level.h"
using namespace Clog;

void LoggerDecoratorDeleter::operator()(LoggerDecorator* ptr) const {
	delete ptr;
}

LoggerFormatter::~LoggerFormatter() = default;

LoggerFormatter::LoggerFormatter(
    std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter> next_one)
    : next_decorator(std::move(next_one)) {
}

std::string LoggerFormatter::run_decorate(const std::string& after_decorate, const CCLoggerLevel level) {
	return next_decorator ? next_decorator->run_decorate(after_decorate, level) : after_decorate;
}
std::string LoggerFormatter::run_decorate(std::string&& after_decorate, const CCLoggerLevel level) {
	return next_decorator ? next_decorator->run_decorate(std::move(after_decorate), level) : after_decorate;
}