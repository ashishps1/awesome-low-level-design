#ifndef PUB_SUB_SYSTEM_HPP
#define PUB_SUB_SYSTEM_HPP

#include <vector>
#include <string>
#include "Topic.hpp"
#include "Subscriber.hpp"

class PubSubSystem {
private:
    std::vector<Topic*> topics;
    std::vector<Subscriber*> subscribers;
    int subscriberIdCounter;

public:
    PubSubSystem();
    ~PubSubSystem();
    
    Topic* createTopic(const std::string& name, const std::string& description);
    void removeTopic(const std::string& topicName);
    
    Subscriber* addSubscriber(const std::string& name);
    void removeSubscriber(const std::string& subscriberId);
    
    bool subscribe(const std::string& subscriberId, const std::string& topicName);
    bool unsubscribe(const std::string& subscriberId, const std::string& topicName);
    bool publish(const std::string& topicName, const std::string& content);
    
    void displayTopics() const;
    void displaySubscribers() const;
    void displaySubscriberMessages(const std::string& subscriberId) const;

private:
    Topic* findTopic(const std::string& topicName) const;
    Subscriber* findSubscriber(const std::string& subscriberId) const;
    std::string generateSubscriberId();
};

#endif 