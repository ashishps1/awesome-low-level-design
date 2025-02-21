#include "Comment.hpp"
#include <iostream>

Comment::Comment(std::string commentId, std::string userId, std::string content)
    : commentId(commentId), userId(userId), content(content) {
    timestamp = std::time(nullptr);
}

std::string Comment::getCommentId() const { return commentId; }
std::string Comment::getUserId() const { return userId; }
std::string Comment::getContent() const { return content; }
std::time_t Comment::getTimestamp() const { return timestamp; }

void Comment::displayInfo() const {
    std::cout << "- " << content << " (by User " << userId << ")" << std::endl;
} 