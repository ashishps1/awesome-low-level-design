#ifndef RIDE_HPP
#define RIDE_HPP

#include <string>
#include <ctime>
#include "User.hpp"
#include "Location.hpp"

enum class RideStatus {
    REQUESTED,
    ACCEPTED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

class Ride {
private:
    std::string rideId;
    User* rider;
    User* driver;
    Location* pickup;
    Location* dropoff;
    double distance;
    double fare;
    std::time_t requestTime;
    std::time_t completionTime;
    RideStatus status;

public:
    Ride(std::string rideId, User* rider, Location* pickup, Location* dropoff);
    ~Ride();
    
    std::string getRideId() const;
    User* getRider() const;
    User* getDriver() const;
    Location* getPickup() const;
    Location* getDropoff() const;
    double getDistance() const;
    double getFare() const;
    std::time_t getRequestTime() const;
    std::time_t getCompletionTime() const;
    RideStatus getStatus() const;
    
    void assignDriver(User* driver);
    void calculateFare();
    void updateStatus(RideStatus status);
    void displayInfo() const;
};

#endif 