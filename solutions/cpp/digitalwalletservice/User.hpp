#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string userId;
    std::string name;
    std::string email;
    std::string phoneNumber;

public:
    User(std::string userId, std::string name, std::string email, std::string phoneNumber);
    
    std::string getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhoneNumber() const;
    void displayInfo() const;
};

#endif 