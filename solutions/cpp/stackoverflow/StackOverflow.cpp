#include "StackOverflow.hpp"
#include <iostream>
#include <algorithm>

StackOverflow::StackOverflow() : userIdCounter(1), postIdCounter(1), commentIdCounter(1) {}

StackOverflow::~StackOverflow() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

User* StackOverflow::registerUser(const std::string& username, const std::string& email) {
    std::string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void StackOverflow::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Post* StackOverflow::addQuestion(const std::string& userId, const std::string& content,
                                const std::vector<std::string>& tags) {
    if (!findUser(userId)) return nullptr;
    
    std::string postId = generatePostId();
    Post* question = new Post(postId, userId, content, tags, PostType::QUESTION);
    posts.push_back(question);
    return question;
}

Post* StackOverflow::addAnswer(const std::string& userId, const std::string& questionId,
                              const std::string& content) {
    if (!findUser(userId)) return nullptr;
    
    Post* question = findPost(questionId);
    if (!question || question->getType() != PostType::QUESTION) return nullptr;
    
    std::string postId = generatePostId();
    Post* answer = new Post(postId, userId, content, std::vector<std::string>(), PostType::ANSWER);
    posts.push_back(answer);
    return answer;
}

Comment* StackOverflow::addComment(const std::string& userId, const std::string& postId,
                                 const std::string& content) {
    if (!findUser(userId)) return nullptr;
    
    Post* post = findPost(postId);
    if (!post) return nullptr;
    
    std::string commentId = generateCommentId();
    Comment* comment = new Comment(commentId, userId, content);
    post->addComment(comment);
    return comment;
}

bool StackOverflow::votePost(const std::string& userId, const std::string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || userId == post->getUserId()) return false;
    
    if (post->addVote(userId)) {
        updateUserReputation(post->getUserId(), 10);  // +10 for upvote
        return true;
    }
    return false;
}

bool StackOverflow::unvotePost(const std::string& userId, const std::string& postId) {
    Post* post = findPost(postId);
    if (!post) return false;
    
    if (post->removeVote(userId)) {
        updateUserReputation(post->getUserId(), -10);  // -10 for removed upvote
        return true;
    }
    return false;
}

bool StackOverflow::acceptAnswer(const std::string& userId, const std::string& answerId) {
    Post* answer = findPost(answerId);
    if (!answer || answer->getType() != PostType::ANSWER) return false;
    
    answer->setAccepted(true);
    updateUserReputation(answer->getUserId(), 15);  // +15 for accepted answer
    return true;
}

std::vector<Post*> StackOverflow::searchQuestions(const std::string& tag) const {
    std::vector<Post*> results;
    for (const auto& post : posts) {
        if (post->getType() == PostType::QUESTION) {
            const auto& tags = post->getTags();
            if (std::find(tags.begin(), tags.end(), tag) != tags.end()) {
                results.push_back(post);
            }
        }
    }
    return results;
}

void StackOverflow::displayUserProfile(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    user->displayInfo();
    
    std::cout << "\nPosts by " << user->getUsername() << ":" << std::endl;
    for (const auto& post : posts) {
        if (post->getUserId() == userId) {
            post->displayInfo();
        }
    }
}

void StackOverflow::displayQuestion(const std::string& questionId) const {
    Post* question = findPost(questionId);
    if (!question || question->getType() != PostType::QUESTION) return;
    
    question->displayInfo();
    
    std::cout << "\nAnswers:" << std::endl;
    for (const auto& post : posts) {
        if (post->getType() == PostType::ANSWER) {
            post->displayInfo();
        }
    }
}

void StackOverflow::displayAllQuestions() const {
    std::cout << "\nAll Questions:" << std::endl;
    for (const auto& post : posts) {
        if (post->getType() == PostType::QUESTION) {
            post->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

User* StackOverflow::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Post* StackOverflow::findPost(const std::string& postId) const {
    auto it = std::find_if(posts.begin(), posts.end(),
        [postId](Post* post) { return post->getPostId() == postId; });
    return it != posts.end() ? *it : nullptr;
}

void StackOverflow::updateUserReputation(const std::string& userId, int points) {
    if (User* user = findUser(userId)) {
        user->updateReputation(points);
    }
}

std::string StackOverflow::generateUserId() {
    return "U" + std::to_string(userIdCounter++);
}

std::string StackOverflow::generatePostId() {
    return "P" + std::to_string(postIdCounter++);
}

std::string StackOverflow::generateCommentId() {
    return "C" + std::to_string(commentIdCounter++);
} 