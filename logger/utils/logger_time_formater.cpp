#include "logger_time_formater.h"
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace Clog;

std::string Clog::time_point_to_string(std::chrono::system_clock::time_point tp) {
	using namespace std::chrono;

	auto t = system_clock::to_time_t(tp);
	std::tm tm;
#ifdef _WIN32
	localtime_s(&tm, &t);
#else
	localtime_r(&t, &tm);
#endif

	auto duration_since_epoch = tp.time_since_epoch();
	auto ms = duration_cast<milliseconds>(duration_since_epoch) - duration_cast<seconds>(duration_since_epoch);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	oss << "." << std::setfill('0') << std::setw(3) << ms.count();
	return oss.str();
}