#include "Topic.hpp"
#include <iostream>
#include <algorithm>

Topic::Topic(std::string name, std::string description)
    : name(name), description(description), active(true) {}

std::string Topic::getName() const { return name; }
std::string Topic::getDescription() const { return description; }
bool Topic::isActive() const { return active; }
const std::vector<Subscriber*>& Topic::getSubscribers() const { return subscribers; }

void Topic::addSubscriber(Subscriber* subscriber) {
    if (!subscriber) return;
    
    auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
    if (it == subscribers.end()) {
        subscribers.push_back(subscriber);
    }
}

void Topic::removeSubscriber(const std::string& subscriberId) {
    auto it = std::find_if(subscribers.begin(), subscribers.end(),
        [subscriberId](Subscriber* sub) { return sub->getId() == subscriberId; });
    
    if (it != subscribers.end()) {
        subscribers.erase(it);
    }
}

void Topic::publishMessage(const Message& message) {
    if (!active) return;
    
    for (auto subscriber : subscribers) {
        subscriber->receiveMessage(message);
    }
}

void Topic::setActive(bool status) {
    active = status;
}

void Topic::displayInfo() const {
    std::cout << "Topic: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Subscribers: " << subscribers.size() << std::endl;
} 