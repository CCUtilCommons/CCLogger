#pragma once
#include "logger_level.h"
#include <type_traits>

namespace Clog {

constexpr auto to_underlying(CCLoggerLevel level) noexcept {
	return static_cast<std::underlying_type_t<CCLoggerLevel>>(level);
}

constexpr bool operator<(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) < to_underlying(rhs);
}

constexpr bool operator>(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) > to_underlying(rhs);
}

constexpr bool operator<=(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) <= to_underlying(rhs);
}

constexpr bool operator>=(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) >= to_underlying(rhs);
}

constexpr bool operator==(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) == to_underlying(rhs);
}

constexpr bool operator!=(CCLoggerLevel lhs, CCLoggerLevel rhs) noexcept {
	return to_underlying(lhs) != to_underlying(rhs);
}

}
