#include "Post.hpp"
#include <iostream>
#include <algorithm>

Post::Post(std::string postId, User* author, std::string content,
           PostType type, std::string timestamp)
    : postId(postId), author(author), content(content),
      type(type), timestamp(timestamp) {}

std::string Post::getPostId() const { return postId; }
User* Post::getAuthor() const { return author; }
std::string Post::getContent() const { return content; }
PostType Post::getType() const { return type; }
std::string Post::getTimestamp() const { return timestamp; }
const std::vector<User*>& Post::getLikes() const { return likes; }
const std::vector<std::string>& Post::getComments() const { return comments; }

void Post::addLike(User* user) {
    if (user && std::find(likes.begin(), likes.end(), user) == likes.end()) {
        likes.push_back(user);
    }
}

void Post::removeLike(User* user) {
    auto it = std::find(likes.begin(), likes.end(), user);
    if (it != likes.end()) {
        likes.erase(it);
    }
}

void Post::addComment(const std::string& comment) {
    comments.push_back(comment);
}

void Post::displayInfo() const {
    std::cout << "\nPost Details:" << std::endl;
    std::cout << "ID: " << postId << std::endl;
    std::cout << "Author: " << author->getProfile()->getName() << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case PostType::TEXT: std::cout << "Text"; break;
        case PostType::IMAGE: std::cout << "Image"; break;
        case PostType::VIDEO: std::cout << "Video"; break;
        case PostType::ARTICLE: std::cout << "Article"; break;
    }
    std::cout << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Likes: " << likes.size() << std::endl;
    std::cout << "Comments: " << comments.size() << std::endl;
    
    if (!comments.empty()) {
        std::cout << "\nComments:" << std::endl;
        for (const auto& comment : comments) {
            std::cout << "- " << comment << std::endl;
        }
    }
} 