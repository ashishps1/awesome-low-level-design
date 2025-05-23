#include "push_notification.h"
#include <iostream>

void PushNotification::send(const std::string& message) {
    std::cout << "Sending push notification: " << message << std::endl;
} 