#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <string>

class Passenger {
private:
    std::string name;
    std::string passportNumber;
    std::string contactNumber;

public:
    Passenger(std::string name, std::string passportNumber, std::string contactNumber);
    
    std::string getName() const;
    std::string getPassportNumber() const;
    std::string getContactNumber() const;
    void displayInfo() const;
};

#endif 