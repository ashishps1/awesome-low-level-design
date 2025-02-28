#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <ctime>

class Message {
private:
    std::string topic;
    std::string content;
    std::time_t timestamp;

public:
    Message(std::string topic, std::string content);
    
    std::string getTopic() const;
    std::string getContent() const;
    std::time_t getTimestamp() const;
    void displayInfo() const;
};

#endif 