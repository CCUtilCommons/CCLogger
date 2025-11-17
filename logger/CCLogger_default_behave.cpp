#include "CCLogger_default_behave.h"
#include "decorator/console_color_decorator.h"
#include "formater.h"
#include "formater/simplify_formarter.h"
#include "formater/standard_formater.h"
#include "io/standard_console.h"
#include <memory>

using namespace Clog;

std::unique_ptr<LoggerIO> Clog::provide_default_io() {
	return std::make_unique<StandardConsoleIO>();
}
std::unique_ptr<LoggerFormatter> Clog::provide_default_formater() {
#ifdef USE_STANDARD_FORMATTER
	return std::unique_ptr<StandardFormater>(
	    new StandardFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	        new ConsoleColorDecorator(), LoggerDecoratorDeleter())));
#else
	return std::unique_ptr<SimplifiedFormater>(
	    new SimplifiedFormater(std::unique_ptr<LoggerDecorator, LoggerDecoratorDeleter>(
	        new ConsoleColorDecorator(), LoggerDecoratorDeleter())));
#endif
}
