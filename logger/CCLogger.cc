#include "CCLogger.hpp"
#include "CCLogger_default_behave.h"
#include "logger_level.h"
#include <algorithm>
#include <memory>
using namespace Clog;

CCLogger::CCLogger() {
	this->formater = provide_default_formater();
	this->default_io = provide_default_io();
}

CCLogger::CCLogger(
    std::unique_ptr<LoggerFormatter> formater,
    // if nullptr, we shell use default io
    std::unique_ptr<LoggerIO> default_io) {
	if (!default_io) {
		this->default_io = provide_default_io();
	} else {
		this->default_io = std::move(default_io);
	}

	if (!formater) {
		this->formater = provide_default_formater();
	} else {
		this->formater = std::move(formater);
	}
}

void CCLogger::log(const std::string& msg,
                   const CCLoggerLevel level,
                   std::source_location loc) {

	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	default_io->write_logger(formats);
	for (auto& io : broadcast_io) {
		io->write_logger(formats);
	}
}

void CCLogger::log(std::string&& msg,
                   const CCLoggerLevel level,
                   std::source_location loc) {
	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	default_io->write_logger(formats);
	for (auto& io : broadcast_io) {
		io->write_logger(formats);
	}
}

void CCLogger::log_direct(const std::string& msg,
                          const CCLoggerLevel level,
                          std::source_location loc) {

	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	default_io->write_logger(formats);
	for (auto& io : broadcast_io) {
		io->write_logger(formats);
	}
}

void CCLogger::log_direct(std::string&& msg,
                          const CCLoggerLevel level,
                          std::source_location loc) {
	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	default_io->write_logger(formats);
	for (auto& io : broadcast_io) {
		io->write_logger(formats);
	}
}

void CCLogger::registerIOBackEnd(std::unique_ptr<LoggerIO> backend) {
	std::lock_guard<std::mutex> _(io_manager_locker);
	broadcast_io.emplace_back(std::move(backend));
}

bool CCLogger::removeIOBackEnd(LoggerIO* backend) {
	std::lock_guard<std::mutex> lg(io_manager_locker);
	auto it = std::find_if(
	    broadcast_io.begin(), broadcast_io.end(),
	    [&](const std::unique_ptr<LoggerIO>& p) {
		    return p.get() == backend;
	    });
	if (it != broadcast_io.end()) {
		broadcast_io.erase(it);
		return true;
	}
	return false;
}
