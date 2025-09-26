#pragma once
#include <chrono>
#include <string>

namespace Clog {

std::string time_point_to_string(std::chrono::system_clock::time_point tp);

}