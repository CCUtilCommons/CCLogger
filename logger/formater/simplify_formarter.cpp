#include "simplify_formarter.h"
#include "logger_level.h"
#include <chrono>
#include <iomanip>
#include <sstream>

#if __cplusplus > 202002L
#include <format>
#include <source_location>
#endif

namespace Clog {

namespace {
	constexpr size_t TIME_WIDTH = 23; // "HH:MM:SS.mmm" 的长度
	constexpr size_t LEVEL_COL_WIDTH = 5; // 日志级别的宽度
	constexpr size_t FILE_LINE_WIDTH = 30; // 文件路径和行号的宽度
	constexpr size_t FUNC_WIDTH = 20; // 函数名的宽度
	// 将日志级别映射为单个字符
	char level_to_char(CCLoggerLevel lvl) {
		switch (lvl) {
		case CCLoggerLevel::Trace:
			return 'T';
		case CCLoggerLevel::Debug:
			return 'D';
		case CCLoggerLevel::Info:
			return 'I';
		case CCLoggerLevel::Warning:
			return 'W';
		case CCLoggerLevel::Error:
			return 'E';
		default:
			return '?';
		}
	}

	// 格式化时间为 "HH:MM:SS.mmm" 的形式
	std::string format_time_hms_ms(std::chrono::system_clock::time_point tp) {
		using namespace std::chrono;
		auto t = system_clock::to_time_t(tp);
		std::tm tm;
#ifdef _WIN32
		localtime_s(&tm, &t);
#else
		localtime_r(&t, &tm);
#endif

		auto dur = tp.time_since_epoch();
		auto ms = duration_cast<milliseconds>(dur) - duration_cast<seconds>(dur);

		std::ostringstream oss;
		oss << std::setfill('0')
		    << std::setw(2) << tm.tm_hour << ":"
		    << std::setw(2) << tm.tm_min << ":"
		    << std::setw(2) << tm.tm_sec << "."
		    << std::setw(3) << ms.count();
		return oss.str();
	}

	// 获取文件路径的文件名部分
	std::string basename_or_tail(const char* path) {
		if (!path)
			return "";
		std::string s(path);
		size_t pos = s.find_last_of("/\\");
		if (pos == std::string::npos)
			return s;
		return s.substr(pos + 1);
	}

	// 将字符串裁剪为指定宽度，超出部分用 "..." 替代
	std::string ellipsize_tail(const std::string& s, size_t width) {
		if (s.size() <= width)
			return s;
		if (width <= 3)
			return s.substr(s.size() - width);
		return std::string("...") + s.substr(s.size() - (width - 3));
	}
}

#if __cplusplus > 202002L
std::string SimplifiedFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {

	std::string time_s = format_time_hms_ms(std::chrono::system_clock::now());

	std::string lvl_char(1, level_to_char(level));

	std::string file_basename = basename_or_tail(context_info.file_name());
	std::string file_line = std::format("{}:{}", file_basename, context_info.line());
	file_line = ellipsize_tail(file_line, FILE_LINE_WIDTH);

	std::string func = context_info.function_name();
	func = ellipsize_tail(func, FUNC_WIDTH);

	std::string body = std::format(
	    "{:<{}}|{:<{}}|{:<{}}|{:<{}}|{}",
	    time_s, TIME_WIDTH,
	    lvl_char, LEVEL_COL_WIDTH,
	    file_line, FILE_LINE_WIDTH,
	    func, FUNC_WIDTH,
	    msg);

	return run_decorate(body, level);
}

std::string SimplifiedFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const std::source_location& context_info) {
	return format(static_cast<const std::string&>(msg), level, context_info);
}
#endif

std::string SimplifiedFormater::format(
    const std::string& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {
	std::string time_s = format_time_hms_ms(std::chrono::system_clock::now());
	std::string lvl_char(1, level_to_char(level));

	std::string file_name = context_info.file_name();
	std::string file_basename = basename_or_tail(file_name.c_str());
	std::ostringstream file_line_ss;
	file_line_ss << file_basename << ":" << context_info.line();
	std::string file_line = ellipsize_tail(file_line_ss.str(), FILE_LINE_WIDTH);

	std::string func = ellipsize_tail(context_info.function_name(), FUNC_WIDTH);

	std::ostringstream body_ss;

	body_ss << std::left << std::setw(TIME_WIDTH) << time_s << "|"
	        << std::left << std::setw(LEVEL_COL_WIDTH) << lvl_char << "|"
	        << std::left << std::setw(FILE_LINE_WIDTH) << file_line << "|"
	        << std::left << std::setw(FUNC_WIDTH) << func << "|"
	        << msg;

	std::string body = body_ss.str();

	return run_decorate(body, level);
}

std::string SimplifiedFormater::format(
    std::string&& msg, const CCLoggerLevel level,
    const CCSourceLocation& context_info) {
	return format(static_cast<const std::string&>(msg), level, context_info);
}

} // namespace Clog
