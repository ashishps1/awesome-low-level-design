#include "StackOverflow.hpp"
#include <iostream>

int main() {
    StackOverflow stackoverflow;
    
    // Register users
    User* user1 = stackoverflow.registerUser("john_doe", "john@email.com");
    User* user2 = stackoverflow.registerUser("alice_smith", "alice@email.com");
    User* user3 = stackoverflow.registerUser("bob_wilson", "bob@email.com");
    
    std::cout << "Initial users:" << std::endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    
    // Add questions
    std::vector<std::string> tags = {"c++", "programming"};
    Post* question1 = stackoverflow.addQuestion(
        user1->getUserId(),
        "How do I use smart pointers in C++?",
        tags
    );
    
    // Add answers
    Post* answer1 = stackoverflow.addAnswer(
        user2->getUserId(),
        question1->getPostId(),
        "Smart pointers automatically manage memory for you..."
    );
    
    Post* answer2 = stackoverflow.addAnswer(
        user3->getUserId(),
        question1->getPostId(),
        "There are three main types of smart pointers..."
    );
    
    // Add comments
    stackoverflow.addComment(
        user1->getUserId(),
        answer1->getPostId(),
        "Thanks, that's helpful!"
    );
    
    // Vote on posts
    stackoverflow.votePost(user2->getUserId(), question1->getPostId());
    stackoverflow.votePost(user3->getUserId(), answer1->getPostId());
    stackoverflow.votePost(user1->getUserId(), answer2->getPostId());
    
    // Accept answer
    stackoverflow.acceptAnswer(user1->getUserId(), answer1->getPostId());
    
    // Display results
    std::cout << "\nQuestion with answers:" << std::endl;
    stackoverflow.displayQuestion(question1->getPostId());
    
    std::cout << "\nUser profiles after activity:" << std::endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    stackoverflow.displayUserProfile(user2->getUserId());
    
    // Search questions
    std::cout << "\nSearching for C++ questions:" << std::endl;
    auto results = stackoverflow.searchQuestions("c++");
    for (const auto& question : results) {
        question->displayInfo();
    }
    
    return 0;
} 