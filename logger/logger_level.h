#pragma once
namespace Clog {
enum class CCLoggerLevel {
	Trace,
	Debug,
	Info,
	Warning,
	Error
}; // Logger should not terminate the Program, so fatal wont be used
}
