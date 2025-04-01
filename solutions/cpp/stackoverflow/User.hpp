#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    int reputation;
    std::vector<std::string> badges;
    bool active;

public:
    User(std::string userId, std::string username, std::string email);
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    int getReputation() const;
    const std::vector<std::string>& getBadges() const;
    bool isActive() const;
    
    void updateReputation(int points);
    void addBadge(const std::string& badge);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 