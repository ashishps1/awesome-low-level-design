#ifndef POST_HPP
#define POST_HPP

#include <string>
#include <vector>
#include "User.hpp"

enum class PostType {
    TEXT,
    IMAGE,
    VIDEO,
    ARTICLE
};

class Post {
private:
    std::string postId;
    User* author;
    std::string content;
    PostType type;
    std::string timestamp;
    std::vector<User*> likes;
    std::vector<std::string> comments;

public:
    Post(std::string postId, User* author, std::string content, 
         PostType type, std::string timestamp);
    
    std::string getPostId() const;
    User* getAuthor() const;
    std::string getContent() const;
    PostType getType() const;
    std::string getTimestamp() const;
    const std::vector<User*>& getLikes() const;
    const std::vector<std::string>& getComments() const;
    
    void addLike(User* user);
    void removeLike(User* user);
    void addComment(const std::string& comment);
    void displayInfo() const;
};

#endif 