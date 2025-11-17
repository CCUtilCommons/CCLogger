#include "blank_formater.h"
#include "CCSourceLocation.h"

using namespace Clog;
#if __cplusplus >= 202002L
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

#endif

std::string BlankFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {

	return run_decorate(msg, level);
}

std::string BlankFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {

	return run_decorate(msg, level);
}
