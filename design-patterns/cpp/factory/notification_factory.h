#pragma once
#include "notification.h"
#include <string>
#include <memory>

class NotificationFactory {
public:
    static std::unique_ptr<Notification> createNotification(const std::string& type);
}; 