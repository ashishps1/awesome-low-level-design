#include "RideService.hpp"
#include <iostream>
#include <algorithm>

RideService::RideService() : userIdCounter(1), rideIdCounter(1) {}

RideService::~RideService() {
    for (auto user : users) delete user;
    for (auto ride : rides) delete ride;
}

User* RideService::registerUser(const std::string& name, const std::string& phone,
                              UserType type, Location* location) {
    std::string userId = generateUserId();
    User* user = new User(userId, name, phone, type, location);
    users.push_back(user);
    return user;
}

void RideService::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Ride* RideService::requestRide(const std::string& riderId, Location* pickup, Location* dropoff) {
    User* rider = findUser(riderId);
    if (!rider || rider->getType() != UserType::RIDER) return nullptr;
    
    std::string rideId = generateRideId();
    Ride* ride = new Ride(rideId, rider, pickup, dropoff);
    rides.push_back(ride);
    
    // Try to find and assign nearest driver
    User* driver = findNearestDriver(*pickup);
    if (driver) {
        ride->assignDriver(driver);
    }
    
    return ride;
}

bool RideService::assignDriver(const std::string& rideId, const std::string& driverId) {
    Ride* ride = findRide(rideId);
    User* driver = findUser(driverId);
    
    if (!ride || !driver || driver->getType() != UserType::DRIVER) return false;
    
    ride->assignDriver(driver);
    return true;
}

bool RideService::updateRideStatus(const std::string& rideId, RideStatus status) {
    Ride* ride = findRide(rideId);
    if (!ride) return false;
    
    ride->updateStatus(status);
    return true;
}

bool RideService::rateUser(const std::string& userId, double rating) {
    User* user = findUser(userId);
    if (!user) return false;
    
    user->updateRating(rating);
    return true;
}

void RideService::displayUsers() const {
    std::cout << "\n=== Registered Users ===" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void RideService::displayRides() const {
    std::cout << "\n=== All Rides ===" << std::endl;
    for (const auto& ride : rides) {
        ride->displayInfo();
    }
}

void RideService::displayUserHistory(const std::string& userId) const {
    std::cout << "\n=== Ride History for User " << userId << " ===" << std::endl;
    for (const auto& ride : rides) {
        if ((ride->getRider()->getUserId() == userId) ||
            (ride->getDriver() && ride->getDriver()->getUserId() == userId)) {
            ride->displayInfo();
        }
    }
}

User* RideService::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Ride* RideService::findRide(const std::string& rideId) const {
    auto it = std::find_if(rides.begin(), rides.end(),
        [rideId](Ride* ride) { return ride->getRideId() == rideId; });
    return it != rides.end() ? *it : nullptr;
}

User* RideService::findNearestDriver(const Location& pickup) const {
    User* nearestDriver = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    
    for (auto user : users) {
        if (user->getType() == UserType::DRIVER && user->isActive()) {
            double distance = pickup.calculateDistance(*user->getCurrentLocation());
            if (distance < minDistance) {
                minDistance = distance;
                nearestDriver = user;
            }
        }
    }
    
    return nearestDriver;
}

std::string RideService::generateUserId() {
    return "U" + std::to_string(userIdCounter++);
}

std::string RideService::generateRideId() {
    return "R" + std::to_string(rideIdCounter++);
} 