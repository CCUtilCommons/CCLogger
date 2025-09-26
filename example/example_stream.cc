#include "CCLoggerStream.h"

int main() {
	Clog::trace << "Hello" << "World!" << 123 << std::endl;
	Clog::debug << "user=" << 123 << " action=login" << std::endl;
	Clog::info << "File loaded: " << "config.yaml" << std::endl;
	Clog::error << "Something went wrong, errno=" << 5 << std::endl;
}
