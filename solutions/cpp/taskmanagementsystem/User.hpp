#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    std::vector<std::string> assignedTasks;  // Task IDs
    bool active;

public:
    User(std::string userId, std::string username, std::string email);
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    const std::vector<std::string>& getAssignedTasks() const;
    bool isActive() const;
    
    void addTask(const std::string& taskId);
    void removeTask(const std::string& taskId);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 