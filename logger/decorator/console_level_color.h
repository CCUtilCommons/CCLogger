#pragma once
#include "logger_level.h"

namespace Clog {

static constexpr const char* ansi_color_reset = "\x1B[0m";
const char* level_to_ansi_color(CCLoggerLevel lvl);

}
