#include "PubSubSystem.hpp"
#include <iostream>
#include <algorithm>

PubSubSystem::PubSubSystem() : subscriberIdCounter(1) {}

PubSubSystem::~PubSubSystem() {
    for (auto topic : topics) delete topic;
    for (auto subscriber : subscribers) delete subscriber;
}

Topic* PubSubSystem::createTopic(const std::string& name, const std::string& description) {
    if (findTopic(name)) return nullptr;
    
    Topic* topic = new Topic(name, description);
    topics.push_back(topic);
    return topic;
}

void PubSubSystem::removeTopic(const std::string& topicName) {
    auto it = std::find_if(topics.begin(), topics.end(),
        [topicName](Topic* topic) { return topic->getName() == topicName; });
    
    if (it != topics.end()) {
        delete *it;
        topics.erase(it);
    }
}

Subscriber* PubSubSystem::addSubscriber(const std::string& name) {
    std::string id = generateSubscriberId();
    Subscriber* subscriber = new Subscriber(id, name);
    subscribers.push_back(subscriber);
    return subscriber;
}

void PubSubSystem::removeSubscriber(const std::string& subscriberId) {
    // Remove from all topics first
    for (auto topic : topics) {
        topic->removeSubscriber(subscriberId);
    }
    
    // Remove from subscribers list
    auto it = std::find_if(subscribers.begin(), subscribers.end(),
        [subscriberId](Subscriber* sub) { return sub->getId() == subscriberId; });
    
    if (it != subscribers.end()) {
        delete *it;
        subscribers.erase(it);
    }
}

bool PubSubSystem::subscribe(const std::string& subscriberId, const std::string& topicName) {
    Topic* topic = findTopic(topicName);
    Subscriber* subscriber = findSubscriber(subscriberId);
    
    if (!topic || !subscriber) return false;
    
    topic->addSubscriber(subscriber);
    return true;
}

bool PubSubSystem::unsubscribe(const std::string& subscriberId, const std::string& topicName) {
    Topic* topic = findTopic(topicName);
    if (!topic) return false;
    
    topic->removeSubscriber(subscriberId);
    return true;
}

bool PubSubSystem::publish(const std::string& topicName, const std::string& content) {
    Topic* topic = findTopic(topicName);
    if (!topic || !topic->isActive()) return false;
    
    Message message(topicName, content);
    topic->publishMessage(message);
    return true;
}

void PubSubSystem::displayTopics() const {
    std::cout << "\nAvailable Topics:" << std::endl;
    for (const auto& topic : topics) {
        topic->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void PubSubSystem::displaySubscribers() const {
    std::cout << "\nRegistered Subscribers:" << std::endl;
    for (const auto& subscriber : subscribers) {
        subscriber->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void PubSubSystem::displaySubscriberMessages(const std::string& subscriberId) const {
    if (Subscriber* subscriber = findSubscriber(subscriberId)) {
        subscriber->displayMessages();
    }
}

Topic* PubSubSystem::findTopic(const std::string& topicName) const {
    auto it = std::find_if(topics.begin(), topics.end(),
        [topicName](Topic* topic) { return topic->getName() == topicName; });
    return it != topics.end() ? *it : nullptr;
}

Subscriber* PubSubSystem::findSubscriber(const std::string& subscriberId) const {
    auto it = std::find_if(subscribers.begin(), subscribers.end(),
        [subscriberId](Subscriber* sub) { return sub->getId() == subscriberId; });
    return it != subscribers.end() ? *it : nullptr;
}

std::string PubSubSystem::generateSubscriberId() {
    return "SUB" + std::to_string(subscriberIdCounter++);
} 