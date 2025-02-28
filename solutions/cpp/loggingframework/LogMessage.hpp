#ifndef LOG_MESSAGE_HPP
#define LOG_MESSAGE_HPP

#include <string>
#include <ctime>
#include "LogLevel.hpp"

class LogMessage {
private:
    LogLevel level;
    std::string message;
    std::string timestamp;
    std::string source;

public:
    LogMessage(LogLevel level, const std::string& message, 
               const std::string& source);
    
    LogLevel getLevel() const;
    std::string getMessage() const;
    std::string getTimestamp() const;
    std::string getSource() const;
    std::string getFormattedMessage() const;
};

#endif 