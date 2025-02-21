#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Item.hpp"

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    double balance;
    std::vector<Item*> listedItems;
    std::vector<Item*> purchasedItems;
    bool active;

public:
    User(std::string userId, std::string username, std::string email);
    ~User();
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    double getBalance() const;
    bool isActive() const;
    const std::vector<Item*>& getListedItems() const;
    const std::vector<Item*>& getPurchasedItems() const;
    
    void addBalance(double amount);
    bool deductBalance(double amount);
    void addListedItem(Item* item);
    void addPurchasedItem(Item* item);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 