#pragma once
#include "CCLoggerExports.h"
#include <string>

#if __cplusplus >= 202002L
#include <source_location>
#endif

#define PLACE_LOC CCSourceLocation().set_file(__FILE__).set_function(__func__).set_line(__LINE__)

struct CCLOG_API CCSourceLocation {

	CCSourceLocation() = default;

	CCSourceLocation(const std::string& file, const std::string& func,
	                 unsigned line, unsigned column)
	    : file_name_(file)
	    , function_name_(func)
	    , line_number(line)
	    , column_number(column) { }

	CCSourceLocation& set_file(const std::string& file) {
		file_name_ = file;
		return *this;
	}

	CCSourceLocation& set_function(const std::string& func) {
		function_name_ = func;
		return *this;
	}

	CCSourceLocation& set_line(unsigned line) {
		line_number = line;
		return *this;
	}

	CCSourceLocation& set_column(unsigned column) {
		column_number = column;
		return *this;
	}

#if __cplusplus >= 202002L
	static CCSourceLocation from_source_location(
	    const std::source_location& sl) {
		return CCSourceLocation {
			sl.file_name(),
			sl.function_name(),
			sl.line(),
			sl.column()
		};
	}

	CCSourceLocation(const std::source_location& sl)
	    : CCSourceLocation { sl.file_name(),
		                     sl.function_name(),
		                     sl.line(),
		                     sl.column() } {
	}
#endif
	/* using for non pain use in C++20 */
	unsigned
	line() const noexcept { return line_number; }

	unsigned
	column() const noexcept { return column_number; }

	std::string
	file_name() const noexcept { return file_name_; }

	std::string
	function_name() const noexcept { return function_name_; }

private:
	std::string file_name_;
	std::string function_name_;
	unsigned line_number = 0;
	unsigned column_number = 0;
};
