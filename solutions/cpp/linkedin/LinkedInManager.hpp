#ifndef LINKEDIN_MANAGER_HPP
#define LINKEDIN_MANAGER_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Post.hpp"

class LinkedInManager {
private:
    std::vector<User*> users;
    std::vector<Post*> posts;
    int postIdCounter;

public:
    LinkedInManager();
    ~LinkedInManager();
    
    void addUser(User* user);
    Post* createPost(std::string userId, std::string content,
                    PostType type, std::string timestamp);
    
    bool addConnection(std::string userId1, std::string userId2);
    bool removeConnection(std::string userId1, std::string userId2);
    
    bool likePost(std::string userId, std::string postId);
    bool unlikePost(std::string userId, std::string postId);
    bool commentOnPost(std::string userId, std::string postId,
                      const std::string& comment);
    
    void displayUserProfile(std::string userId) const;
    void displayUserConnections(std::string userId) const;
    void displayUserPosts(std::string userId) const;
    void displayAllUsers() const;
    
private:
    User* findUser(const std::string& userId) const;
    Post* findPost(const std::string& postId) const;
    std::string generatePostId();
};

#endif 