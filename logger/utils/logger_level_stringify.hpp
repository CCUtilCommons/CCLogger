#pragma once
#include "logger_level.h"
#include <string>
namespace Clog {

inline std::string stringify_level(const CCLoggerLevel level) {
	switch (level) {
	case CCLoggerLevel::Trace:
		return "[Trace]";
	case CCLoggerLevel::Info:
		return "[Info]";
	case CCLoggerLevel::Debug:
		return "[Debug]";
	case CCLoggerLevel::Warning:
		return "[Warning]";
	case CCLoggerLevel::Error:
		return "[Error]";
	}
	return "[?]";
}

}
