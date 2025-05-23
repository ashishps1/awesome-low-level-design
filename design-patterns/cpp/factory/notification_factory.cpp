#include "notification_factory.h"
#include "email_notification.h"
#include "sms_notification.h"
#include "push_notification.h"
#include <stdexcept>

std::unique_ptr<Notification> NotificationFactory::createNotification(const std::string& type) {
    if (type == "EMAIL") {
        return std::make_unique<EmailNotification>();
    } else if (type == "SMS") {
        return std::make_unique<SMSNotification>();
    } else if (type == "PUSH") {
        return std::make_unique<PushNotification>();
    }
    throw std::invalid_argument("Unknown notification type");
} 