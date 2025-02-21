#ifndef STACK_OVERFLOW_HPP
#define STACK_OVERFLOW_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Post.hpp"
#include "Comment.hpp"

class StackOverflow {
private:
    std::vector<User*> users;
    std::vector<Post*> posts;
    int userIdCounter;
    int postIdCounter;
    int commentIdCounter;

public:
    StackOverflow();
    ~StackOverflow();
    
    // User management
    User* registerUser(const std::string& username, const std::string& email);
    void removeUser(const std::string& userId);
    
    // Post management
    Post* addQuestion(const std::string& userId, const std::string& content,
                     const std::vector<std::string>& tags);
    Post* addAnswer(const std::string& userId, const std::string& questionId,
                   const std::string& content);
    Comment* addComment(const std::string& userId, const std::string& postId,
                       const std::string& content);
    
    // Voting and acceptance
    bool votePost(const std::string& userId, const std::string& postId);
    bool unvotePost(const std::string& userId, const std::string& postId);
    bool acceptAnswer(const std::string& userId, const std::string& answerId);
    
    // Search and display
    std::vector<Post*> searchQuestions(const std::string& tag) const;
    void displayUserProfile(const std::string& userId) const;
    void displayQuestion(const std::string& questionId) const;
    void displayAllQuestions() const;

private:
    User* findUser(const std::string& userId) const;
    Post* findPost(const std::string& postId) const;
    void updateUserReputation(const std::string& userId, int points);
    std::string generateUserId();
    std::string generatePostId();
    std::string generateCommentId();
};

#endif 