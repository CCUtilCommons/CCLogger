#include "standard_console.h"
#include <iostream>

bool StandardConsoleIO::write_logger(const std::string& log_info) {
	// Dont Use std::endl, as it
	// will auto flush the console
	std::cout << log_info << '\n';

	return true; // We here think the flush always OK
}

bool StandardConsoleIO::flush() {
	std::cout << std::flush; // Flush the console
	return true; // We here think the flush always OK
}