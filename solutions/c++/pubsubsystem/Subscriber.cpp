#include "Subscriber.hpp"
#include <iostream>

Subscriber::Subscriber(std::string id, std::string name)
    : id(id), name(name), active(true) {}

std::string Subscriber::getId() const { return id; }
std::string Subscriber::getName() const { return name; }
bool Subscriber::isActive() const { return active; }
const std::vector<Message>& Subscriber::getMessageQueue() const { return messageQueue; }

void Subscriber::receiveMessage(const Message& message) {
    if (active) {
        messageQueue.push_back(message);
    }
}

void Subscriber::displayMessages() const {
    std::cout << "\nMessages for " << name << ":" << std::endl;
    if (messageQueue.empty()) {
        std::cout << "No messages" << std::endl;
        return;
    }
    
    for (const auto& message : messageQueue) {
        message.displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void Subscriber::clearMessages() {
    messageQueue.clear();
}

void Subscriber::setActive(bool status) {
    active = status;
}

void Subscriber::displayInfo() const {
    std::cout << "Subscriber: " << name << " (ID: " << id << ")" << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Pending Messages: " << messageQueue.size() << std::endl;
} 