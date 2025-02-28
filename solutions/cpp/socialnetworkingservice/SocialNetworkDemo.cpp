#include "SocialNetwork.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    SocialNetwork network;
    
    // Register users
    User* user1 = network.registerUser("john_doe", "john@email.com");
    User* user2 = network.registerUser("jane_smith", "jane@email.com");
    User* user3 = network.registerUser("bob_wilson", "bob@email.com");
    
    std::cout << "Initial users:" << std::endl;
    network.displayAllUsers();
    
    // Add friends
    network.addFriend(user1->getUserId(), user2->getUserId());
    network.addFriend(user2->getUserId(), user3->getUserId());
    
    // Create posts
    Post* post1 = network.createPost(user1->getUserId(), "Hello, world!");
    Post* post2 = network.createPost(user2->getUserId(), "Having a great day!");
    
    // Like and comment on posts
    network.likePost(user2->getUserId(), post1->getPostId());
    network.likePost(user3->getUserId(), post1->getPostId());
    network.addComment(post1->getPostId(), "Great post!");
    
    network.likePost(user1->getUserId(), post2->getPostId());
    network.addComment(post2->getPostId(), "Glad to hear that!");
    
    // Display user profiles and posts
    std::cout << "\nUser Profiles and Posts:" << std::endl;
    network.displayUserProfile(user1->getUserId());
    network.displayUserFriends(user1->getUserId());
    network.displayUserPosts(user1->getUserId());
    
    network.displayUserProfile(user2->getUserId());
    network.displayUserFriends(user2->getUserId());
    network.displayUserPosts(user2->getUserId());
    
    // Remove a friend and display updated info
    network.removeFriend(user1->getUserId(), user2->getUserId());
    std::cout << "\nAfter removing friendship:" << std::endl;
    network.displayUserFriends(user1->getUserId());
    
    return 0;
} 