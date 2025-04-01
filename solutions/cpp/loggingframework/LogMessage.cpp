#include "LogMessage.hpp"
#include <sstream>
#include <iomanip>

LogMessage::LogMessage(LogLevel level, const std::string& message, 
                      const std::string& source)
    : level(level), message(message), source(source) {
    // Get current timestamp
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = oss.str();
}

LogLevel LogMessage::getLevel() const { return level; }
std::string LogMessage::getMessage() const { return message; }
std::string LogMessage::getTimestamp() const { return timestamp; }
std::string LogMessage::getSource() const { return source; }

std::string LogMessage::getFormattedMessage() const {
    std::ostringstream oss;
    oss << "[" << timestamp << "] "
        << "[" << logLevelToString(level) << "] "
        << "[" << source << "] "
        << message;
    return oss.str();
} 