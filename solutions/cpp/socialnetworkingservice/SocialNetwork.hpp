#ifndef SOCIAL_NETWORK_HPP
#define SOCIAL_NETWORK_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Post.hpp"

class SocialNetwork {
private:
    std::vector<User*> users;
    std::vector<Post*> posts;
    int userIdCounter;
    int postIdCounter;

public:
    SocialNetwork();
    ~SocialNetwork();
    
    // User management
    User* registerUser(const std::string& username, const std::string& email);
    void removeUser(const std::string& userId);
    bool addFriend(const std::string& userId1, const std::string& userId2);
    bool removeFriend(const std::string& userId1, const std::string& userId2);
    
    // Post management
    Post* createPost(const std::string& userId, const std::string& content);
    bool likePost(const std::string& userId, const std::string& postId);
    bool unlikePost(const std::string& userId, const std::string& postId);
    bool addComment(const std::string& postId, const std::string& comment);
    
    // Display functions
    void displayUserProfile(const std::string& userId) const;
    void displayUserFriends(const std::string& userId) const;
    void displayUserPosts(const std::string& userId) const;
    void displayAllUsers() const;
    void displayAllPosts() const;

private:
    User* findUser(const std::string& userId) const;
    Post* findPost(const std::string& postId) const;
    std::string generateUserId();
    std::string generatePostId();
};

#endif 