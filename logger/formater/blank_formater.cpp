#include "blank_formater.h"

using namespace Clog;

std::string BlankFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {

	return run_decorate(msg, level);
}

std::string BlankFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {

	return run_decorate(msg, level);
}
