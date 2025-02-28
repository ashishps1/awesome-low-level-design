#ifndef POST_HPP
#define POST_HPP

#include <string>
#include <vector>
#include <ctime>

class Post {
private:
    std::string postId;
    std::string userId;
    std::string content;
    std::time_t timestamp;
    std::vector<std::string> likes;  // Vector of userIds who liked
    std::vector<std::string> comments;

public:
    Post(std::string postId, std::string userId, std::string content);
    
    std::string getPostId() const;
    std::string getUserId() const;
    std::string getContent() const;
    std::time_t getTimestamp() const;
    const std::vector<std::string>& getLikes() const;
    const std::vector<std::string>& getComments() const;
    
    void addLike(const std::string& userId);
    void removeLike(const std::string& userId);
    void addComment(const std::string& comment);
    void displayInfo() const;
};

#endif 