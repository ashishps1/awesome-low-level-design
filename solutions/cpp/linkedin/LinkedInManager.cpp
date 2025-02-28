#include "LinkedInManager.hpp"
#include <iostream>

LinkedInManager::LinkedInManager() : postIdCounter(1) {}

LinkedInManager::~LinkedInManager() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

void LinkedInManager::addUser(User* user) {
    users.push_back(user);
}

Post* LinkedInManager::createPost(std::string userId, std::string content,
                                PostType type, std::string timestamp) {
    User* user = findUser(userId);
    if (!user || !user->isActive()) return nullptr;
    
    Post* post = new Post(generatePostId(), user, content, type, timestamp);
    posts.push_back(post);
    user->addPost(post);
    return post;
}

bool LinkedInManager::addConnection(std::string userId1, std::string userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2 || !user1->isActive() || !user2->isActive()) {
        return false;
    }
    
    user1->addConnection(user2);
    return true;
}

bool LinkedInManager::removeConnection(std::string userId1, std::string userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2) return false;
    
    user1->removeConnection(user2);
    return true;
}

bool LinkedInManager::likePost(std::string userId, std::string postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || !user->isActive()) return false;
    
    post->addLike(user);
    return true;
}

bool LinkedInManager::unlikePost(std::string userId, std::string postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->removeLike(user);
    return true;
}

bool LinkedInManager::commentOnPost(std::string userId, std::string postId,
                                  const std::string& comment) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || !user->isActive()) return false;
    
    post->addComment(comment);
    return true;
}

void LinkedInManager::displayUserProfile(std::string userId) const {
    User* user = findUser(userId);
    if (user) {
        user->displayInfo();
    }
}

void LinkedInManager::displayUserConnections(std::string userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nConnections for " << user->getEmail() << ":" << std::endl;
    for (const auto& connection : user->getConnections()) {
        connection->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void LinkedInManager::displayUserPosts(std::string userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nPosts by " << user->getEmail() << ":" << std::endl;
    for (const auto& post : user->getPosts()) {
        post->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void LinkedInManager::displayAllUsers() const {
    std::cout << "\nAll Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

User* LinkedInManager::findUser(const std::string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Post* LinkedInManager::findPost(const std::string& postId) const {
    for (auto post : posts) {
        if (post->getPostId() == postId) return post;
    }
    return nullptr;
}

std::string LinkedInManager::generatePostId() {
    return "P" + std::to_string(postIdCounter++);
} 