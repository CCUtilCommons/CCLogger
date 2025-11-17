#include "CCLogger.hpp"
#include "CCLogger_default_behave.h"
#include "CCSourceLocation.h"
#include "CCThreadPool.h"
#include "logger_level.h"
#include <algorithm>
#include <memory>
using namespace Clog;

void ThreadPoolDeleter::operator()(CCThreadPool::CCThreadPool* ptr) const {
	delete ptr; // shutdown the thread pool
}

CCLogger::CCLogger() {
	this->formater = provide_default_formater();
	this->default_io = provide_default_io();

	// Ok provide a pools
	log_worker_pool = std::unique_ptr<CCThreadPool::CCThreadPool, ThreadPoolDeleter>(
	    new CCThreadPool::CCThreadPool(
	        std::make_unique<CCThreadPool::ThreadCountDefaultProvider>()));
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

	// Ok provide a pools
	log_worker_pool = std::unique_ptr<CCThreadPool::CCThreadPool, ThreadPoolDeleter>(
	    new CCThreadPool::CCThreadPool(
	        std::make_unique<CCThreadPool::ThreadCountDefaultProvider>()));
}

CCLogger::~CCLogger() {
	for (const auto& io : broadcast_io) {
		io.first->flush();
	}
}

#if __cplusplus >= 202002L
void CCLogger::log(const std::string& msg,
                   const CCLoggerLevel level,
                   std::source_location loc) {
	auto task = [this,
	             msg_copy = msg,
	             level,
	             loc]() mutable {
		this->log_direct(msg_copy, level, loc);
	};

	try {
		log_worker_pool->enTask(std::move(task));
	} catch (const ThreadPoolTerminateError& e) {
		this->log_direct(msg, level, loc);
	} catch (...) {
		this->log_direct(msg, level, loc);
	}
}

void CCLogger::log(std::string&& msg,
                   const CCLoggerLevel level,
                   std::source_location loc) {
	auto task = [this,
	             msg_moved = std::move(msg), // 移动 msg，避免复制
	             level,
	             loc]() mutable {
		this->log_direct(std::move(msg_moved), level, loc);
	};

	try {
		log_worker_pool->enTask(std::move(task));
	} catch (...) {
		// Abolished the logger sessions
	}
}

void CCLogger::log_direct(const std::string& msg,
                          const CCLoggerLevel level,
                          std::source_location loc) {

	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	if (!silent_defbackend)
		default_io->write_logger(formats);

	for (auto& io_ptr : broadcast_io) {
		std::string formats_copy = formats;
		LoggerIO* target_io = io_ptr.first.get();
		formats = io_ptr.second->format(
		    std::move(msg), level, loc);

		auto broadcast_task = [this,
		                       formats_copy,
		                       target_io]() {
			target_io->write_logger(formats_copy);
		};

		try {
			log_worker_pool->enTask(std::move(broadcast_task));
		} catch (...) {
			target_io->write_logger(formats_copy);
		}
	}
}

void CCLogger::log_direct(std::string&& msg,
                          const CCLoggerLevel level,
                          std::source_location loc) {
	auto formats = formater->format(
	    msg, level, loc);
	std::lock_guard<std::mutex> _(io_manager_locker);
	if (!silent_defbackend)
		default_io->write_logger(formats);

	// broadcast to multi backends
	for (auto& io_ptr : broadcast_io) {
		LoggerIO* target_io = io_ptr.first.get();
		std::string formats_copy = io_ptr.second->format(
		    std::move(msg), level, loc);

		auto broadcast_task = [this,
		                       formats_copy,
		                       target_io]() {
			target_io->write_logger(formats_copy);
		};

		try {
			log_worker_pool->enTask(std::move(broadcast_task));
		} catch (...) {
			target_io->write_logger(formats_copy);
		}
	}
}
#endif

void CCLogger::log(const std::string& msg,
                   const CCLoggerLevel level,
                   const CCSourceLocation& loc) {
	auto task = [this,
	             msg_copy = msg,
	             level,
	             loc]() mutable {
		this->log_direct(msg_copy, level, loc);
	};

	try {
		log_worker_pool->enTask(std::move(task));
	} catch (const ThreadPoolTerminateError& e) {
		this->log_direct(msg, level, loc);
	} catch (...) {
		this->log_direct(msg, level, loc);
	}
}

void CCLogger::log(std::string&& msg,
                   const CCLoggerLevel level,
                   const CCSourceLocation& loc) {
	auto task = [this,
	             msg_moved = std::move(msg),
	             level,
	             loc]() mutable {
		this->log_direct(std::move(msg_moved), level, loc);
	};

	try {
		log_worker_pool->enTask(std::move(task));
	} catch (...) {
		// Abolished the logger sessions
	}
}

void CCLogger::log_direct(const std::string& msg,
                          const CCLoggerLevel level,
                          const CCSourceLocation& loc) {

	auto formats = formater->format(
	    msg, level, loc);

	std::lock_guard<std::mutex> _(io_manager_locker);
	if (!silent_defbackend)
		default_io->write_logger(formats);

	for (auto& io_ptr : broadcast_io) {
		LoggerIO* target_io = io_ptr.first.get();
		std::string formats_copy = io_ptr.second->format(
		    std::move(msg), level, loc);

		auto broadcast_task = [this,
		                       formats_copy,
		                       target_io]() {
			target_io->write_logger(formats_copy);
		};

		try {
			log_worker_pool->enTask(std::move(broadcast_task));
		} catch (...) {
			target_io->write_logger(formats_copy);
		}
	}
}

void CCLogger::log_direct(std::string&& msg,
                          const CCLoggerLevel level,
                          const CCSourceLocation& loc) {
	auto formats = formater->format(
	    msg, level, loc);
	std::lock_guard<std::mutex> _(io_manager_locker);
	if (!silent_defbackend)
		default_io->write_logger(formats);

	// broadcast to multi backends
	for (auto& io_ptr : broadcast_io) {
		LoggerIO* target_io = io_ptr.first.get();
		std::string formats_copy = io_ptr.second->format(
		    std::move(msg), level, loc);
		auto broadcast_task = [this,
		                       formats_copy,
		                       target_io]() {
			target_io->write_logger(formats_copy);
		};

		try {
			log_worker_pool->enTask(std::move(broadcast_task));
		} catch (...) {
			target_io->write_logger(formats_copy);
		}
	}
}

void CCLogger::registerIOBackEnd(std::unique_ptr<LoggerIO> backend, std::unique_ptr<LoggerFormatter> formater) {
	std::lock_guard<std::mutex> _(io_manager_locker);
	broadcast_io.insert(
	    std::make_pair(std::move(backend), std::move(formater)));
}

bool CCLogger::removeIOBackEnd(LoggerIO* backend) {
	std::lock_guard<std::mutex> lg(io_manager_locker);

	auto it = std::find_if(
	    broadcast_io.begin(), broadcast_io.end(),
	    [&](const auto& pair) {
		    return pair.first.get() == backend;
	    });
	if (it != broadcast_io.end()) {
		broadcast_io.erase(it);
		return true;
	}
	return false;
}
