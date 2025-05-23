#include "notification_factory.h"
#include <iostream>

int main() {
    try {
        // Create different types of notifications using the factory
        auto emailNotification = NotificationFactory::createNotification("EMAIL");
        auto smsNotification = NotificationFactory::createNotification("SMS");
        auto pushNotification = NotificationFactory::createNotification("PUSH");

        // Send messages using the notifications
        emailNotification->send("Hello via Email!");
        smsNotification->send("Hello via SMS!");
        pushNotification->send("Hello via Push!");

        // Try to create an invalid notification type
        auto invalidNotification = NotificationFactory::createNotification("INVALID");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
} 