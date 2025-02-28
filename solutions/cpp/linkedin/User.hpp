#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Profile.hpp"
#include "Post.hpp"

class User {
private:
    std::string userId;
    std::string email;
    std::string password;
    Profile* profile;
    std::vector<User*> connections;
    std::vector<Post*> posts;
    bool active;

public:
    User(std::string userId, std::string email, std::string password);
    ~User();
    
    std::string getUserId() const;
    std::string getEmail() const;
    Profile* getProfile() const;
    bool isActive() const;
    const std::vector<User*>& getConnections() const;
    const std::vector<Post*>& getPosts() const;
    
    void setProfile(Profile* profile);
    void addConnection(User* user);
    void removeConnection(User* user);
    void addPost(Post* post);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 