#include "console_level_color.h"

using namespace Clog;
const char* Clog::level_to_ansi_color(CCLoggerLevel lvl) {
	switch (lvl) {
	case CCLoggerLevel::Trace:
		return "\x1B[90m"; // Gray
	case CCLoggerLevel::Debug:
		return "\x1B[36m"; // Cyan
	case CCLoggerLevel::Info:
		return "\x1B[32m"; // Green
	case CCLoggerLevel::Warning:
		return "\x1B[33m"; // Yellow
	case CCLoggerLevel::Error:
		return "\x1B[1;31m"; // Bold Red
	default:
		return "\x1B[0m";
	}
}
