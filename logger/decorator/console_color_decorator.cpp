#include "console_color_decorator.h"
#include "decorator/console_level_color.h"

using namespace Clog;

std::string ConsoleColorDecorator::
    make_decorate(const std::string& formatted, const CCLoggerLevel level) {
	return level_to_ansi_color(level) + formatted + ansi_color_reset;
}

std::string ConsoleColorDecorator::
    make_decorate(std::string&& formatted, const CCLoggerLevel level) {
	return level_to_ansi_color(level) + std::move(formatted) + ansi_color_reset;
}