#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "Location.hpp"

enum class UserType {
    RIDER,
    DRIVER
};

class User {
private:
    std::string userId;
    std::string name;
    std::string phone;
    UserType type;
    Location* currentLocation;
    bool active;
    double rating;
    int totalRatings;

public:
    User(std::string userId, std::string name, std::string phone, UserType type,
         Location* location);
    ~User();
    
    std::string getUserId() const;
    std::string getName() const;
    std::string getPhone() const;
    UserType getType() const;
    Location* getCurrentLocation() const;
    bool isActive() const;
    double getRating() const;
    
    void updateLocation(Location* location);
    void setActive(bool status);
    void updateRating(double newRating);
    void displayInfo() const;
};

#endif 