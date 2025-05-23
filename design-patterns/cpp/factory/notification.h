#pragma once
#include <string>

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send(const std::string& message) = 0;
}; 