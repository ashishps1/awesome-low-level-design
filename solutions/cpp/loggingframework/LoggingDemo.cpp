#include "Logger.hpp"
#include "ConsoleAppender.hpp"
#include "FileAppender.hpp"
#include <memory>

int main() {
    // Create logger
    Logger logger("MyApp");
    
    // Add console appender
    auto consoleAppender = std::make_shared<ConsoleAppender>();
    logger.addAppender(consoleAppender);
    
    // Add file appender
    auto fileAppender = std::make_shared<FileAppender>("app.log");
    logger.addAppender(fileAppender);
    
    // Log messages at different levels
    logger.trace("This is a trace message");  // Won't be logged (below INFO)
    logger.debug("This is a debug message");  // Won't be logged (below INFO)
    logger.info("Application started");
    logger.warn("This is a warning message");
    logger.error("An error occurred");
    logger.fatal("Fatal error: application shutting down");
    
    // Change minimum log level
    logger.setMinLevel(LogLevel::DEBUG);
    logger.debug("Now debug messages will be logged");
    
    return 0;
} 