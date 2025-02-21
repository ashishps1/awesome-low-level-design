#ifndef CONSOLE_APPENDER_HPP
#define CONSOLE_APPENDER_HPP

#include "LogAppender.hpp"

class ConsoleAppender : public LogAppender {
public:
    void append(const LogMessage& message) override;
};

#endif 