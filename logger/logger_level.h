#pragma once
#include "CCLoggerExports.h"
namespace Clog {
enum class CCLOG_API CCLoggerLevel {
	Trace,
	Debug,
	Info,
	Warning,
	Error
}; // Logger should not terminate the Program, so fatal wont be used
}
