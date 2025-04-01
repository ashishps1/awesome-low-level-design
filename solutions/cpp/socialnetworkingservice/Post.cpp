#include "Post.hpp"
#include <iostream>
#include <algorithm>

Post::Post(std::string postId, std::string userId, std::string content)
    : postId(postId), userId(userId), content(content) {
    timestamp = std::time(nullptr);
}

std::string Post::getPostId() const { return postId; }
std::string Post::getUserId() const { return userId; }
std::string Post::getContent() const { return content; }
std::time_t Post::getTimestamp() const { return timestamp; }
const std::vector<std::string>& Post::getLikes() const { return likes; }
const std::vector<std::string>& Post::getComments() const { return comments; }

void Post::addLike(const std::string& userId) {
    if (std::find(likes.begin(), likes.end(), userId) == likes.end()) {
        likes.push_back(userId);
    }
}

void Post::removeLike(const std::string& userId) {
    auto it = std::find(likes.begin(), likes.end(), userId);
    if (it != likes.end()) {
        likes.erase(it);
    }
}

void Post::addComment(const std::string& comment) {
    comments.push_back(comment);
}

void Post::displayInfo() const {
    std::cout << "\nPost ID: " << postId << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Time: " << std::ctime(&timestamp);
    std::cout << "Likes: " << likes.size() << std::endl;
    
    if (!comments.empty()) {
        std::cout << "Comments:" << std::endl;
        for (const auto& comment : comments) {
            std::cout << "- " << comment << std::endl;
        }
    }
} 