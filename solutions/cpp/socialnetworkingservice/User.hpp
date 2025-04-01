#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include <set>

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    std::set<std::string> friends;  // Set of friend userIds
    bool active;

public:
    User(std::string userId, std::string username, std::string email);
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    const std::set<std::string>& getFriends() const;
    bool isActive() const;
    
    void addFriend(const std::string& friendId);
    void removeFriend(const std::string& friendId);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 