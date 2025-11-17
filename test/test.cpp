#include "CCLogger.hpp"
#include "decorator/console_color_decorator.h"
#include "formater/simplify_formarter.h"
#include "io/fileio.h"
#include "io/null_io.hpp"
#include "io/standard_console.h"
#include <atomic>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace Clog;

#if __cplusplus >= 202002L

/* ========== 压力测试 ========== */
void stress_test() {
	CCLogger logger;

	logger.registerIOBackEnd(std::make_unique<FileLoggerIO>("stress.log"));
	logger.setDefBackendSilent(true);
	constexpr int THREADS = 100;
	constexpr int TASKS_PER_THREAD = 2000;
	std::atomic<int> counter { 0 };

	auto worker = [&]() {
		for (int i = 0; i < TASKS_PER_THREAD; i++) {
			logger.log("Message " + std::to_string(i),
			           CCLoggerLevel::Info);
			counter++;
		}
	};

	std::vector<std::thread> pool;
	for (int i = 0; i < THREADS; i++) {
		pool.emplace_back(worker);
	}
	for (auto& t : pool)
		t.join();

	assert(counter == THREADS * TASKS_PER_THREAD);
	std::cout << "[Stress Test] Finished " << counter.load() << " logs\n";
}

/* ========== 性能测试 ========== */
void perf_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<FileLoggerIO>("perf.log"));
	logger.setDefBackendSilent(true);
	constexpr int TASKS = 200000;

	std::ofstream csv("perf_result.csv");
	csv << "threads,tasks_per_thread,total_tasks,time_s,tps\n";

	for (int threads = 1; threads <= 32; threads *= 2) {
		int per_thread = TASKS / threads;

		auto start = std::chrono::high_resolution_clock::now();

		std::vector<std::thread> pool;
		for (int t = 0; t < threads; t++) {
			pool.emplace_back([&]() {
				for (int i = 0; i < per_thread; i++) {
					logger.log("Perf test message",
					           CCLoggerLevel::Debug);
				}
			});
		}
		for (auto& th : pool)
			th.join();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		double tps = TASKS / diff.count();

		csv << threads << "," << per_thread << "," << TASKS << ","
		    << diff.count() << "," << tps << "\n";

		std::cout << "[Perf Test] threads=" << threads
		          << " tasks=" << TASKS
		          << " time=" << diff.count()
		          << "s TPS=" << tps << "\n";
	}
	csv.close();
}

/* ========== 边缘测试 ========== */
void edge_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<StandardConsoleIO>());

	// 1. 空消息
	logger.log("", CCLoggerLevel::Warning);

	// 2. 超长消息
	std::string long_msg(1024 * 1024, 'A');
	logger.log(long_msg, CCLoggerLevel::Error);

	// 3. 移除不存在的 IO
	bool removed = logger.removeIOBackEnd(reinterpret_cast<LoggerIO*>(0xdeadbeef));
	assert(!removed);

	// 4. 快速创建销毁
	for (int i = 0; i < 1000; i++) {
		CCLogger tmp(
		    std::unique_ptr<SimplifiedFormater>(
		        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
		            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
		    std::make_unique<StandardConsoleIO>());
		tmp.log("Temp logger test", CCLoggerLevel::Info);
	}

	std::cout << "[Edge Test] Finished\n";
}

void nullio_perf_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<NullIO>());

	constexpr int TASKS = 1'000'000; // 100万日志

	std::ofstream csv("nullio_perf_result.csv");
	csv << "threads,tasks_per_thread,total_tasks,time_s,tps\n";

	for (int threads = 1; threads <= 64; threads *= 2) {
		int per_thread = TASKS / threads;

		auto start = std::chrono::high_resolution_clock::now();

		std::vector<std::thread> pool;
		for (int t = 0; t < threads; t++) {
			pool.emplace_back([&]() {
				for (int i = 0; i < per_thread; i++) {
					logger.log("NullIO test message",
					           CCLoggerLevel::Debug);
				}
			});
		}
		for (auto& th : pool)
			th.join();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		double tps = TASKS / diff.count();

		csv << threads << "," << per_thread << "," << TASKS << ","
		    << diff.count() << "," << tps << "\n";

		std::cout << "[NullIO Perf Test] threads=" << threads
		          << " tasks=" << TASKS
		          << " time=" << diff.count()
		          << "s TPS=" << tps << "\n";
	}
}
#else
/* ========== 压力测试 ========== */
void stress_test() {
	CCLogger logger;

	logger.registerIOBackEnd(std::make_unique<FileLoggerIO>("stress.log"));
	logger.setDefBackendSilent(true);
	constexpr int THREADS = 100;
	constexpr int TASKS_PER_THREAD = 2000;
	std::atomic<int> counter { 0 };

	auto worker = [&]() {
		for (int i = 0; i < TASKS_PER_THREAD; i++) {
			logger.log("Message " + std::to_string(i),
			           CCLoggerLevel::Info, PLACE_LOC);
			counter++;
		}
	};

	std::vector<std::thread> pool;
	for (int i = 0; i < THREADS; i++) {
		pool.emplace_back(worker);
	}
	for (auto& t : pool)
		t.join();

	assert(counter == THREADS * TASKS_PER_THREAD);
	std::cout << "[Stress Test] Finished " << counter.load() << " logs\n";
}

/* ========== 性能测试 ========== */
void perf_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<FileLoggerIO>("perf.log"));
	logger.setDefBackendSilent(true);
	constexpr int TASKS = 200000;

	std::ofstream csv("perf_result.csv");
	csv << "threads,tasks_per_thread,total_tasks,time_s,tps\n";

	for (int threads = 1; threads <= 32; threads *= 2) {
		int per_thread = TASKS / threads;

		auto start = std::chrono::high_resolution_clock::now();

		std::vector<std::thread> pool;
		for (int t = 0; t < threads; t++) {
			pool.emplace_back([&]() {
				for (int i = 0; i < per_thread; i++) {
					logger.log("Perf test message",
					           CCLoggerLevel::Debug, PLACE_LOC);
				}
			});
		}
		for (auto& th : pool)
			th.join();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		double tps = TASKS / diff.count();

		csv << threads << "," << per_thread << "," << TASKS << ","
		    << diff.count() << "," << tps << "\n";

		std::cout << "[Perf Test] threads=" << threads
		          << " tasks=" << TASKS
		          << " time=" << diff.count()
		          << "s TPS=" << tps << "\n";
	}
	csv.close();
}

/* ========== 边缘测试 ========== */
void edge_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<StandardConsoleIO>());

	// 1. 空消息
	logger.log("", CCLoggerLevel::Warning, PLACE_LOC);

	// 2. 超长消息
	std::string long_msg(1024 * 1024, 'A');
	logger.log(long_msg, CCLoggerLevel::Error, PLACE_LOC);

	// 3. 移除不存在的 IO
	bool removed = logger.removeIOBackEnd(reinterpret_cast<LoggerIO*>(0xdeadbeef));
	assert(!removed);

	// 4. 快速创建销毁
	for (int i = 0; i < 1000; i++) {
		CCLogger tmp(
		    std::unique_ptr<SimplifiedFormater>(
		        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
		            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
		    std::make_unique<StandardConsoleIO>());
		tmp.log("Temp logger test", CCLoggerLevel::Info, PLACE_LOC);
	}

	std::cout << "[Edge Test] Finished\n";
}

void nullio_perf_test() {
	CCLogger logger(
	    std::unique_ptr<SimplifiedFormater>(
	        new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	            new ConsoleColorDecorator(), LoggerDecoratorDeleter()))),
	    std::make_unique<NullIO>());

	constexpr int TASKS = 1'000'000; // 100万日志

	std::ofstream csv("nullio_perf_result.csv");
	csv << "threads,tasks_per_thread,total_tasks,time_s,tps\n";

	for (int threads = 1; threads <= 64; threads *= 2) {
		int per_thread = TASKS / threads;

		auto start = std::chrono::high_resolution_clock::now();

		std::vector<std::thread> pool;
		for (int t = 0; t < threads; t++) {
			pool.emplace_back([&]() {
				for (int i = 0; i < per_thread; i++) {
					logger.log("NullIO test message",
					           CCLoggerLevel::Debug, PLACE_LOC);
				}
			});
		}
		for (auto& th : pool)
			th.join();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		double tps = TASKS / diff.count();

		csv << threads << "," << per_thread << "," << TASKS << ","
		    << diff.count() << "," << tps << "\n";

		std::cout << "[NullIO Perf Test] threads=" << threads
		          << " tasks=" << TASKS
		          << " time=" << diff.count()
		          << "s TPS=" << tps << "\n";
	}
}

#endif

/* ========== 主函数 ========== */
int main() {
	stress_test();
	perf_test();
	nullio_perf_test();
	edge_test();
	return 0;
}
