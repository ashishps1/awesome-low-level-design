#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>
#include <memory>
#include "LogLevel.hpp"
#include "LogMessage.hpp"
#include "LogAppender.hpp"

class Logger {
private:
    std::string name;
    LogLevel minLevel;
    std::vector<std::shared_ptr<LogAppender>> appenders;

public:
    Logger(const std::string& name, LogLevel minLevel = LogLevel::INFO);
    
    void addAppender(std::shared_ptr<LogAppender> appender);
    void setMinLevel(LogLevel level);
    
    void log(LogLevel level, const std::string& message);
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void fatal(const std::string& message);

private:
    bool isLevelEnabled(LogLevel level) const;
};

#endif 