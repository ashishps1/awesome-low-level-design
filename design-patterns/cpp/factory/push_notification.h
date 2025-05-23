#pragma once
#include "notification.h"

class PushNotification : public Notification {
public:
    void send(const std::string& message) override;
}; 