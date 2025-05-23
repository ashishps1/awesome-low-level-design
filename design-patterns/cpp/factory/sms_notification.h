#pragma once
#include "notification.h"

class SMSNotification : public Notification {
public:
    void send(const std::string& message) override;
}; 