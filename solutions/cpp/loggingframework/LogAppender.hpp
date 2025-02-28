#ifndef LOG_APPENDER_HPP
#define LOG_APPENDER_HPP

#include "LogMessage.hpp"

class LogAppender {
public:
    virtual ~LogAppender() = default;
    virtual void append(const LogMessage& message) = 0;
};

#endif 