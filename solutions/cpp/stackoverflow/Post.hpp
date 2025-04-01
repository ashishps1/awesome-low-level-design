#ifndef POST_HPP
#define POST_HPP

#include <string>
#include <vector>
#include <ctime>
#include "Comment.hpp"

enum class PostType {
    QUESTION,
    ANSWER
};

class Post {
private:
    std::string postId;
    std::string userId;
    std::string content;
    std::vector<std::string> tags;
    std::vector<Comment*> comments;
    std::vector<std::string> votes;  // userIds who voted
    int score;
    bool accepted;
    PostType type;
    std::time_t timestamp;

public:
    Post(std::string postId, std::string userId, std::string content,
         const std::vector<std::string>& tags, PostType type);
    ~Post();
    
    std::string getPostId() const;
    std::string getUserId() const;
    std::string getContent() const;
    const std::vector<std::string>& getTags() const;
    const std::vector<Comment*>& getComments() const;
    int getScore() const;
    bool isAccepted() const;
    PostType getType() const;
    std::time_t getTimestamp() const;
    
    void addComment(Comment* comment);
    bool addVote(const std::string& userId);
    bool removeVote(const std::string& userId);
    void setAccepted(bool status);
    void displayInfo() const;
};

#endif 