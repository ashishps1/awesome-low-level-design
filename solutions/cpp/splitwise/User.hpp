#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>

class User {
private:
    std::string userId;
    std::string name;
    std::string email;
    std::map<std::string, double> balances;  // userId -> amount
    bool active;

public:
    User(std::string userId, std::string name, std::string email);
    
    std::string getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    bool isActive() const;
    double getBalanceWith(const std::string& userId) const;
    const std::map<std::string, double>& getBalances() const;
    
    void updateBalance(const std::string& userId, double amount);
    void setActive(bool status);
    void displayInfo() const;
    void displayBalances() const;
};

#endif 