#ifndef GUEST_HPP
#define GUEST_HPP

#include <string>

class Guest {
private:
    std::string guestId;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;

public:
    Guest(std::string guestId, std::string name, std::string email,
          std::string phone, std::string address);
    
    std::string getGuestId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getAddress() const;
    void displayInfo() const;
};

#endif 