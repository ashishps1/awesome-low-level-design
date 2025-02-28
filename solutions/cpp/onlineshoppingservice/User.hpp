#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Order.hpp"

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    std::string address;
    std::vector<Order*> orders;
    bool active;

public:
    User(std::string userId, std::string username, std::string email, std::string address);
    ~User();
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getAddress() const;
    bool isActive() const;
    const std::vector<Order*>& getOrders() const;
    
    void addOrder(Order* order);
    void setActive(bool status);
    void displayInfo() const;
    void displayOrders() const;
};

#endif 