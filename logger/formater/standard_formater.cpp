#include "standard_formater.h"
#include "CCSourceLocation.h"
#include "utils/logger_level_stringify.hpp"
#include "utils/logger_time_formater.h"
#include <iomanip>
#include <sstream>

#if __cplusplus > 202002L
#include <format>
#include <source_location>
#endif

using namespace Clog;

namespace {
constexpr size_t TIME_WIDTH = 23; // "YYYY-MM-DD HH:MM:SS.mmm" ≈ 23
constexpr size_t LEVEL_COL_WIDTH = 9; // e.g. "[Warning]" 长度 9 -> 保证所有等级对齐
constexpr size_t FILE_LINE_WIDTH = 30; // 文件:行 最大显示宽度（含省略）
constexpr size_t FUNC_WIDTH = 20; // 函数名最多显示的宽度

std::string basename_or_tail(const char* path) {
	if (!path)
		return "";
	std::string s(path);
	size_t pos = s.find_last_of("/\\");
	if (pos == std::string::npos)
		return s;
	return s.substr(pos + 1);
}

std::string ellipsize_tail(const std::string& s, size_t width) {
	if (s.size() <= width)
		return s;
	if (width <= 3)
		return s.substr(s.size() - width);
	return std::string("...") + s.substr(s.size() - (width - 3));
}

};

#if __cplusplus > 202002L
std::string StandardFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {

	std::string time_s = time_point_to_string(std::chrono::system_clock::now());

	std::string lvl_inner = stringify_level(level);
	std::string lvl_bracket = std::format("{}", lvl_inner); // e.g. "[Warning]"

	std::string file_basename = basename_or_tail(context_info.file_name());
	std::string file_line = std::format("{}:{}", file_basename, context_info.line());
	file_line = ellipsize_tail(file_line, FILE_LINE_WIDTH);

	std::string func = context_info.function_name();
	func = ellipsize_tail(func, FUNC_WIDTH);

	std::string level_field = std::format("{:<{}}", lvl_bracket, LEVEL_COL_WIDTH);
	std::string file_field = std::format("{:<{}}", file_line, FILE_LINE_WIDTH);
	std::string func_field = std::format("{:<{}}", func, FUNC_WIDTH);

	std::string body = std::format(
	    "{} | {} | {} | {} | {}",
	    time_s,
	    level_field,
	    file_field,
	    func_field,
	    msg);
	return run_decorate(body, level);
}

std::string StandardFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {
	return format(static_cast<const std::string&>(msg), level, context_info);
}
#endif

std::string StandardFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {

	std::string time_s = time_point_to_string(std::chrono::system_clock::now());

	std::string lvl_inner = stringify_level(level);
	std::string lvl_bracket = "[" + lvl_inner + "]"; // e.g. "[Warning]"

	std::string file_name = context_info.file_name();
	std::string file_basename = basename_or_tail(file_name.c_str());
	std::ostringstream file_line_ss;
	file_line_ss << file_basename << ":" << context_info.line();
	std::string file_line = ellipsize_tail(file_line_ss.str(), FILE_LINE_WIDTH);
	std::string func = ellipsize_tail(context_info.function_name(), FUNC_WIDTH);

	std::ostringstream level_field_ss;
	level_field_ss << std::left << std::setw(LEVEL_COL_WIDTH) << lvl_bracket;
	std::string level_field = level_field_ss.str();

	std::ostringstream file_field_ss;
	file_field_ss << std::left << std::setw(FILE_LINE_WIDTH) << file_line;
	std::string file_field = file_field_ss.str();

	std::ostringstream func_field_ss;
	func_field_ss << std::left << std::setw(FUNC_WIDTH) << func;
	std::string func_field = func_field_ss.str();

	std::ostringstream body_ss;
	body_ss << time_s << " | "
	        << level_field << " | "
	        << file_field << " | "
	        << func_field << " | "
	        << msg;

	std::string body = body_ss.str();

	return run_decorate(body, level);
}

std::string StandardFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {
	return format(static_cast<const std::string&>(msg), level, context_info);
}
