#pragma once
#include "formater.h"
#include "logger_io.h"
#include <memory>
namespace Clog {

std::unique_ptr<LoggerIO> provide_default_io();
std::unique_ptr<LoggerFormatter> provide_default_formater();
std::unique_ptr<LoggerFormatter> provide_blank_formater();

}
