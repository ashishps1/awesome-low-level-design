#include "PubSubSystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    PubSubSystem system;
    
    // Create topics
    Topic* tech = system.createTopic("Technology", "Tech news and updates");
    Topic* sports = system.createTopic("Sports", "Sports news and scores");
    Topic* weather = system.createTopic("Weather", "Weather updates");
    
    std::cout << "Initial topics:" << std::endl;
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
    std::cout << "\nPublishing messages..." << std::endl;
    
    system.publish("Technology", "New AI breakthrough!");
    system.publish("Sports", "Team A wins championship!");
    system.publish("Weather", "Sunny weather expected");
    
    // Small delay to simulate time passing
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Display messages for each subscriber
    std::cout << "\nChecking messages for subscribers:" << std::endl;
    system.displaySubscriberMessages(sub1->getId());
    system.displaySubscriberMessages(sub2->getId());
    system.displaySubscriberMessages(sub3->getId());
    
    // Unsubscribe and test
    std::cout << "\nUnsubscribing John from Weather..." << std::endl;
    system.unsubscribe(sub1->getId(), "Weather");
    
    system.publish("Weather", "Storm warning!");
    
    std::cout << "\nJohn's updated messages:" << std::endl;
    system.displaySubscriberMessages(sub1->getId());
    
    return 0;
} 