#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <string>
#include <ctime>

class Comment {
private:
    std::string commentId;
    std::string userId;
    std::string content;
    std::time_t timestamp;

public:
    Comment(std::string commentId, std::string userId, std::string content);
    
    std::string getCommentId() const;
    std::string getUserId() const;
    std::string getContent() const;
    std::time_t getTimestamp() const;
    
    void displayInfo() const;
};

#endif 