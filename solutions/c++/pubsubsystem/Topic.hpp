#ifndef TOPIC_HPP
#define TOPIC_HPP

#include <string>
#include <vector>
#include "Subscriber.hpp"

class Topic {
private:
    std::string name;
    std::string description;
    std::vector<Subscriber*> subscribers;
    bool active;

public:
    Topic(std::string name, std::string description);
    
    std::string getName() const;
    std::string getDescription() const;
    bool isActive() const;
    const std::vector<Subscriber*>& getSubscribers() const;
    
    void addSubscriber(Subscriber* subscriber);
    void removeSubscriber(const std::string& subscriberId);
    void publishMessage(const Message& message);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 