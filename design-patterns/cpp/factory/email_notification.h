#pragma once
#include "notification.h"

class EmailNotification : public Notification {
public:
    void send(const std::string& message) override;
}; 