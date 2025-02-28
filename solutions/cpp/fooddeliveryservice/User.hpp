#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string userId;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;

public:
    User(std::string userId, std::string name, std::string email, 
         std::string phone, std::string address);
    
    std::string getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getAddress() const;
    void displayInfo() const;
};

#endif 