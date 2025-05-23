#include "sms_notification.h"
#include <iostream>

void SMSNotification::send(const std::string& message) {
    std::cout << "Sending SMS: " << message << std::endl;
} 