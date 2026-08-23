// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Message;
class Subscriber;
class Topic;
class PubSubSystem;

// ===== Message.hpp =====
class Message {
private:
    string topic;
    string content;
    time_t timestamp;

public:
    Message(string topic, string content);
    
    string getTopic() const;
    string getContent() const;
    time_t getTimestamp() const;
    void displayInfo() const;
};

// ===== Subscriber.hpp =====
class Subscriber {
private:
    string id;
    string name;
    vector<Message> messageQueue;
    bool active;

public:
    Subscriber(string id, string name);
    
    string getId() const;
    string getName() const;
    bool isActive() const;
    const vector<Message>& getMessageQueue() const;
    
    void receiveMessage(const Message& message);
    void displayMessages() const;
    void clearMessages();
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Topic.hpp =====
class Topic {
private:
    string name;
    string description;
    vector<Subscriber*> subscribers;
    bool active;

public:
    Topic(string name, string description);
    
    string getName() const;
    string getDescription() const;
    bool isActive() const;
    const vector<Subscriber*>& getSubscribers() const;
    
    void addSubscriber(Subscriber* subscriber);
    void removeSubscriber(const string& subscriberId);
    void publishMessage(const Message& message);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== PubSubSystem.hpp =====
class PubSubSystem {
private:
    vector<Topic*> topics;
    vector<Subscriber*> subscribers;
    int subscriberIdCounter;

public:
    PubSubSystem();
    ~PubSubSystem();
    
    Topic* createTopic(const string& name, const string& description);
    void removeTopic(const string& topicName);
    
    Subscriber* addSubscriber(const string& name);
    void removeSubscriber(const string& subscriberId);
    
    bool subscribe(const string& subscriberId, const string& topicName);
    bool unsubscribe(const string& subscriberId, const string& topicName);
    bool publish(const string& topicName, const string& content);
    
    void displayTopics() const;
    void displaySubscribers() const;
    void displaySubscriberMessages(const string& subscriberId) const;

private:
    Topic* findTopic(const string& topicName) const;
    Subscriber* findSubscriber(const string& subscriberId) const;
    string generateSubscriberId();
};

// ===== Message.cpp =====
Message::Message(string topic, string content)
    : topic(topic), content(content) {
    timestamp = time(nullptr);
}

string Message::getTopic() const { return topic; }
string Message::getContent() const { return content; }
time_t Message::getTimestamp() const { return timestamp; }

void Message::displayInfo() const {
    cout << "Topic: " << topic << endl;
    cout << "Content: " << content << endl;
    cout << "Time: " << ctime(&timestamp);
} 

// ===== PubSubSystem.cpp =====
PubSubSystem::PubSubSystem() : subscriberIdCounter(1) {}

PubSubSystem::~PubSubSystem() {
    for (auto topic : topics) delete topic;
    for (auto subscriber : subscribers) delete subscriber;
}

Topic* PubSubSystem::createTopic(const string& name, const string& description) {
    if (findTopic(name)) return nullptr;
    
    Topic* topic = new Topic(name, description);
    topics.push_back(topic);
    return topic;
}

void PubSubSystem::removeTopic(const string& topicName) {
    auto it = find_if(topics.begin(), topics.end(),
        [topicName](Topic* topic) { return topic->getName() == topicName; });
    
    if (it != topics.end()) {
        delete *it;
        topics.erase(it);
    }
}

Subscriber* PubSubSystem::addSubscriber(const string& name) {
    string id = generateSubscriberId();
    Subscriber* subscriber = new Subscriber(id, name);
    subscribers.push_back(subscriber);
    return subscriber;
}

void PubSubSystem::removeSubscriber(const string& subscriberId) {
    // Remove from all topics first
    for (auto topic : topics) {
        topic->removeSubscriber(subscriberId);
    }
    
    // Remove from subscribers list
    auto it = find_if(subscribers.begin(), subscribers.end(),
        [subscriberId](Subscriber* sub) { return sub->getId() == subscriberId; });
    
    if (it != subscribers.end()) {
        delete *it;
        subscribers.erase(it);
    }
}

bool PubSubSystem::subscribe(const string& subscriberId, const string& topicName) {
    Topic* topic = findTopic(topicName);
    Subscriber* subscriber = findSubscriber(subscriberId);
    
    if (!topic || !subscriber) return false;
    
    topic->addSubscriber(subscriber);
    return true;
}

bool PubSubSystem::unsubscribe(const string& subscriberId, const string& topicName) {
    Topic* topic = findTopic(topicName);
    if (!topic) return false;
    
    topic->removeSubscriber(subscriberId);
    return true;
}

bool PubSubSystem::publish(const string& topicName, const string& content) {
    Topic* topic = findTopic(topicName);
    if (!topic || !topic->isActive()) return false;
    
    Message message(topicName, content);
    topic->publishMessage(message);
    return true;
}

void PubSubSystem::displayTopics() const {
    cout << "\nAvailable Topics:" << endl;
    for (const auto& topic : topics) {
        topic->displayInfo();
        cout << "------------------------" << endl;
    }
}

void PubSubSystem::displaySubscribers() const {
    cout << "\nRegistered Subscribers:" << endl;
    for (const auto& subscriber : subscribers) {
        subscriber->displayInfo();
        cout << "------------------------" << endl;
    }
}

void PubSubSystem::displaySubscriberMessages(const string& subscriberId) const {
    if (Subscriber* subscriber = findSubscriber(subscriberId)) {
        subscriber->displayMessages();
    }
}

Topic* PubSubSystem::findTopic(const string& topicName) const {
    auto it = find_if(topics.begin(), topics.end(),
        [topicName](Topic* topic) { return topic->getName() == topicName; });
    return it != topics.end() ? *it : nullptr;
}

Subscriber* PubSubSystem::findSubscriber(const string& subscriberId) const {
    auto it = find_if(subscribers.begin(), subscribers.end(),
        [subscriberId](Subscriber* sub) { return sub->getId() == subscriberId; });
    return it != subscribers.end() ? *it : nullptr;
}

string PubSubSystem::generateSubscriberId() {
    return "SUB" + to_string(subscriberIdCounter++);
} 

// ===== Subscriber.cpp =====
Subscriber::Subscriber(string id, string name)
    : id(id), name(name), active(true) {}

string Subscriber::getId() const { return id; }
string Subscriber::getName() const { return name; }
bool Subscriber::isActive() const { return active; }
const vector<Message>& Subscriber::getMessageQueue() const { return messageQueue; }

void Subscriber::receiveMessage(const Message& message) {
    if (active) {
        messageQueue.push_back(message);
    }
}

void Subscriber::displayMessages() const {
    cout << "\nMessages for " << name << ":" << endl;
    if (messageQueue.empty()) {
        cout << "No messages" << endl;
        return;
    }
    
    for (const auto& message : messageQueue) {
        message.displayInfo();
        cout << "------------------------" << endl;
    }
}

void Subscriber::clearMessages() {
    messageQueue.clear();
}

void Subscriber::setActive(bool status) {
    active = status;
}

void Subscriber::displayInfo() const {
    cout << "Subscriber: " << name << " (ID: " << id << ")" << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Pending Messages: " << messageQueue.size() << endl;
} 

// ===== Topic.cpp =====
Topic::Topic(string name, string description)
    : name(name), description(description), active(true) {}

string Topic::getName() const { return name; }
string Topic::getDescription() const { return description; }
bool Topic::isActive() const { return active; }
const vector<Subscriber*>& Topic::getSubscribers() const { return subscribers; }

void Topic::addSubscriber(Subscriber* subscriber) {
    if (!subscriber) return;
    
    auto it = find(subscribers.begin(), subscribers.end(), subscriber);
    if (it == subscribers.end()) {
        subscribers.push_back(subscriber);
    }
}

void Topic::removeSubscriber(const string& subscriberId) {
    auto it = find_if(subscribers.begin(), subscribers.end(),
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
    cout << "Topic: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Subscribers: " << subscribers.size() << endl;
} 

// ===== PubSubDemo.cpp =====
int main() {
    PubSubSystem system;
    
    // Create topics
    Topic* tech = system.createTopic("Technology", "Tech news and updates");
    Topic* sports = system.createTopic("Sports", "Sports news and scores");
    Topic* weather = system.createTopic("Weather", "Weather updates");
    
    cout << "Initial topics:" << endl;
    system.displayTopics();
    
    // Add subscribers
    Subscriber* sub1 = system.addSubscriber("John");
    Subscriber* sub2 = system.addSubscriber("Alice");
    Subscriber* sub3 = system.addSubscriber("Bob");
    
    // Subscribe to topics
    system.subscribe(sub1->getId(), "Technology");
    system.subscribe(sub1->getId(), "Weather");
    system.subscribe(sub2->getId(), "Sports");
    system.subscribe(sub3->getId(), "Technology");
    system.subscribe(sub3->getId(), "Sports");
    
    // Publish messages
    cout << "\nPublishing messages..." << endl;
    
    system.publish("Technology", "New AI breakthrough!");
    system.publish("Sports", "Team A wins championship!");
    system.publish("Weather", "Sunny weather expected");
    
    // Small delay to simulate time passing
    this_thread::sleep_for(chrono::seconds(1));
    
    // Display messages for each subscriber
    cout << "\nChecking messages for subscribers:" << endl;
    system.displaySubscriberMessages(sub1->getId());
    system.displaySubscriberMessages(sub2->getId());
    system.displaySubscriberMessages(sub3->getId());
    
    // Unsubscribe and test
    cout << "\nUnsubscribing John from Weather..." << endl;
    system.unsubscribe(sub1->getId(), "Weather");
    
    system.publish("Weather", "Storm warning!");
    
    cout << "\nJohn's updated messages:" << endl;
    system.displaySubscriberMessages(sub1->getId());
    
    return 0;
} 

