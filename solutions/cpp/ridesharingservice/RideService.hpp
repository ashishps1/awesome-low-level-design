#ifndef RIDE_SERVICE_HPP
#define RIDE_SERVICE_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Ride.hpp"

class RideService {
private:
    std::vector<User*> users;
    std::vector<Ride*> rides;
    int userIdCounter;
    int rideIdCounter;

public:
    RideService();
    ~RideService();
    
    User* registerUser(const std::string& name, const std::string& phone,
                      UserType type, Location* location);
    void removeUser(const std::string& userId);
    
    Ride* requestRide(const std::string& riderId, Location* pickup, Location* dropoff);
    bool assignDriver(const std::string& rideId, const std::string& driverId);
    bool updateRideStatus(const std::string& rideId, RideStatus status);
    bool rateUser(const std::string& userId, double rating);
    
    void displayUsers() const;
    void displayRides() const;
    void displayUserHistory(const std::string& userId) const;

private:
    User* findUser(const std::string& userId) const;
    Ride* findRide(const std::string& rideId) const;
    User* findNearestDriver(const Location& pickup) const;
    std::string generateUserId();
    std::string generateRideId();
};

#endif 