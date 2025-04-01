#include "Post.hpp"
#include <iostream>
#include <algorithm>

Post::Post(std::string postId, std::string userId, std::string content,
           const std::vector<std::string>& tags, PostType type)
    : postId(postId), userId(userId), content(content), tags(tags),
      score(0), accepted(false), type(type) {
    timestamp = std::time(nullptr);
}

Post::~Post() {
    for (auto comment : comments) {
        delete comment;
    }
}

std::string Post::getPostId() const { return postId; }
std::string Post::getUserId() const { return userId; }
std::string Post::getContent() const { return content; }
const std::vector<std::string>& Post::getTags() const { return tags; }
const std::vector<Comment*>& Post::getComments() const { return comments; }
int Post::getScore() const { return score; }
bool Post::isAccepted() const { return accepted; }
PostType Post::getType() const { return type; }
std::time_t Post::getTimestamp() const { return timestamp; }

void Post::addComment(Comment* comment) {
    comments.push_back(comment);
}

bool Post::addVote(const std::string& userId) {
    if (std::find(votes.begin(), votes.end(), userId) == votes.end()) {
        votes.push_back(userId);
        score++;
        return true;
    }
    return false;
}

bool Post::removeVote(const std::string& userId) {
    auto it = std::find(votes.begin(), votes.end(), userId);
    if (it != votes.end()) {
        votes.erase(it);
        score--;
        return true;
    }
    return false;
}

void Post::setAccepted(bool status) {
    accepted = status;
}

void Post::displayInfo() const {
    std::cout << "\nPost ID: " << postId << std::endl;
    std::cout << "Type: " << (type == PostType::QUESTION ? "Question" : "Answer") << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Status: " << (accepted ? "Accepted" : "Not Accepted") << std::endl;
    
    if (!tags.empty()) {
        std::cout << "Tags: ";
        for (const auto& tag : tags) {
            std::cout << tag << " ";
        }
        std::cout << std::endl;
    }
    
    if (!comments.empty()) {
        std::cout << "Comments:" << std::endl;
        for (const auto& comment : comments) {
            comment->displayInfo();
        }
    }
    
    std::cout << "Time: " << std::ctime(&timestamp);
} 