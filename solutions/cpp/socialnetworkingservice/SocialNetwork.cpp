#include "SocialNetwork.hpp"
#include <iostream>
#include <algorithm>

SocialNetwork::SocialNetwork() : userIdCounter(1), postIdCounter(1) {}

SocialNetwork::~SocialNetwork() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

User* SocialNetwork::registerUser(const std::string& username, const std::string& email) {
    std::string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void SocialNetwork::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        // Remove user from friends lists
        for (auto user : users) {
            user->removeFriend(userId);
        }
        
        // Remove user's posts
        posts.erase(
            std::remove_if(posts.begin(), posts.end(),
                [userId](Post* post) { return post->getUserId() == userId; }),
            posts.end()
        );
        
        delete *it;
        users.erase(it);
    }
}

bool SocialNetwork::addFriend(const std::string& userId1, const std::string& userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2 || userId1 == userId2) return false;
    
    user1->addFriend(userId2);
    user2->addFriend(userId1);
    return true;
}

bool SocialNetwork::removeFriend(const std::string& userId1, const std::string& userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2) return false;
    
    user1->removeFriend(userId2);
    user2->removeFriend(userId1);
    return true;
}

Post* SocialNetwork::createPost(const std::string& userId, const std::string& content) {
    if (!findUser(userId)) return nullptr;
    
    std::string postId = generatePostId();
    Post* post = new Post(postId, userId, content);
    posts.push_back(post);
    return post;
}

bool SocialNetwork::likePost(const std::string& userId, const std::string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->addLike(userId);
    return true;
}

bool SocialNetwork::unlikePost(const std::string& userId, const std::string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->removeLike(userId);
    return true;
}

bool SocialNetwork::addComment(const std::string& postId, const std::string& comment) {
    Post* post = findPost(postId);
    if (!post) return false;
    
    post->addComment(comment);
    return true;
}

void SocialNetwork::displayUserProfile(const std::string& userId) const {
    User* user = findUser(userId);
    if (user) {
        std::cout << "\nUser Profile:" << std::endl;
        user->displayInfo();
    }
}

void SocialNetwork::displayUserFriends(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nFriends of " << user->getUsername() << ":" << std::endl;
    for (const auto& friendId : user->getFriends()) {
        if (User* friend_ = findUser(friendId)) {
            std::cout << "- " << friend_->getUsername() << std::endl;
        }
    }
}

void SocialNetwork::displayUserPosts(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nPosts by " << user->getUsername() << ":" << std::endl;
    for (const auto& post : posts) {
        if (post->getUserId() == userId) {
            post->displayInfo();
        }
    }
}

void SocialNetwork::displayAllUsers() const {
    std::cout << "\nAll Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void SocialNetwork::displayAllPosts() const {
    std::cout << "\nAll Posts:" << std::endl;
    for (const auto& post : posts) {
        post->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

User* SocialNetwork::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Post* SocialNetwork::findPost(const std::string& postId) const {
    auto it = std::find_if(posts.begin(), posts.end(),
        [postId](Post* post) { return post->getPostId() == postId; });
    return it != posts.end() ? *it : nullptr;
}

std::string SocialNetwork::generateUserId() {
    return "U" + std::to_string(userIdCounter++);
}

std::string SocialNetwork::generatePostId() {
    return "P" + std::to_string(postIdCounter++);
} 