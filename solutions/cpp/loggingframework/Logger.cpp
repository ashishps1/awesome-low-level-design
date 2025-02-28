#include "Logger.hpp"

Logger::Logger(const std::string& name, LogLevel minLevel)
    : name(name), minLevel(minLevel) {}

void Logger::addAppender(std::shared_ptr<LogAppender> appender) {
    appenders.push_back(appender);
}

void Logger::setMinLevel(LogLevel level) {
    minLevel = level;
}

bool Logger::isLevelEnabled(LogLevel level) const {
    return static_cast<int>(level) >= static_cast<int>(minLevel);
}

void Logger::log(LogLevel level, const std::string& message) {
    if (!isLevelEnabled(level)) return;
    
    LogMessage logMessage(level, message, name);
    for (const auto& appender : appenders) {
        appender->append(logMessage);
    }
}

void Logger::trace(const std::string& message) {
    log(LogLevel::TRACE, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::fatal(const std::string& message) {
    log(LogLevel::FATAL, message);
} 