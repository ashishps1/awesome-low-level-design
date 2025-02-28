#include "User.hpp"
#include <iostream>
#include <iomanip>

User::User(std::string userId, std::string name, std::string phone, UserType type,
           Location* location)
    : userId(userId), name(name), phone(phone), type(type),
      currentLocation(location), active(true), rating(5.0), totalRatings(0) {}

User::~User() {
    delete currentLocation;
}

std::string User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getPhone() const { return phone; }
UserType User::getType() const { return type; }
Location* User::getCurrentLocation() const { return currentLocation; }
bool User::isActive() const { return active; }
double User::getRating() const { return rating; }

void User::updateLocation(Location* location) {
    delete currentLocation;
    currentLocation = location;
}

void User::setActive(bool status) {
    active = status;
}

void User::updateRating(double newRating) {
    if (newRating >= 1.0 && newRating <= 5.0) {
        rating = ((rating * totalRatings) + newRating) / (totalRatings + 1);
        totalRatings++;
    }
}

void User::displayInfo() const {
    std::cout << "User: " << name << " (ID: " << userId << ")" << std::endl;
    std::cout << "Type: " << (type == UserType::RIDER ? "Rider" : "Driver") << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Rating: " << std::fixed << std::setprecision(1) << rating << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    if (currentLocation) {
        currentLocation->displayInfo();
    }
} 