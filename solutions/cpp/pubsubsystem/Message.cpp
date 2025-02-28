#include "Message.hpp"
#include <iostream>

Message::Message(std::string topic, std::string content)
    : topic(topic), content(content) {
    timestamp = std::time(nullptr);
}

std::string Message::getTopic() const { return topic; }
std::string Message::getContent() const { return content; }
std::time_t Message::getTimestamp() const { return timestamp; }

void Message::displayInfo() const {
    std::cout << "Topic: " << topic << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Time: " << std::ctime(&timestamp);
} 