#include "LinkedInManager.hpp"
#include <iostream>

int main() {
    LinkedInManager linkedin;
    
    // Create users
    User* user1 = new User("U001", "john@example.com", "password123");
    User* user2 = new User("U002", "jane@example.com", "password456");
    
    // Create profiles
    Profile* profile1 = new Profile("John Doe", "Software Engineer");
    Profile* profile2 = new Profile("Jane Smith", "Product Manager");
    
    user1->setProfile(profile1);
    user2->setProfile(profile2);
    
    // Add skills
    profile1->addSkill("C++");
    profile1->addSkill("Python");
    profile2->addSkill("Product Management");
    profile2->addSkill("Agile");
    
    // Add experience
    Experience exp1{"Tech Corp", "Software Engineer", "2020", "Present",
                   "Developing enterprise applications"};
    profile1->addExperience(exp1);
    
    // Add education
    Education edu1{"University of Tech", "BS", "Computer Science",
                  "2016", "2020"};
    profile1->addEducation(edu1);
    
    linkedin.addUser(user1);
    linkedin.addUser(user2);
    
    // Create connection
    linkedin.addConnection("U001", "U002");
    
    // Create posts
    Post* post = linkedin.createPost("U001", "Hello LinkedIn!",
                                   PostType::TEXT, "2024-01-01");
    if (post) {
        linkedin.likePost("U002", post->getPostId());
        linkedin.commentOnPost("U002", post->getPostId(),
                             "Great to see you here!");
    }
    
    // Display information
    std::cout << "User Profiles:" << std::endl;
    linkedin.displayUserProfile("U001");
    linkedin.displayUserProfile("U002");
    
    std::cout << "\nUser Connections:" << std::endl;
    linkedin.displayUserConnections("U001");
    
    std::cout << "\nUser Posts:" << std::endl;
    linkedin.displayUserPosts("U001");
    
    return 0;
} 