#include "Ride.hpp"
#include <iostream>
#include <iomanip>

Ride::Ride(std::string rideId, User* rider, Location* pickup, Location* dropoff)
    : rideId(rideId), rider(rider), driver(nullptr), pickup(pickup), dropoff(dropoff),
      distance(0.0), fare(0.0), status(RideStatus::REQUESTED) {
    requestTime = std::time(nullptr);
    completionTime = 0;
    distance = pickup->calculateDistance(*dropoff);
}

Ride::~Ride() {
    delete pickup;
    delete dropoff;
}

std::string Ride::getRideId() const { return rideId; }
User* Ride::getRider() const { return rider; }
User* Ride::getDriver() const { return driver; }
Location* Ride::getPickup() const { return pickup; }
Location* Ride::getDropoff() const { return dropoff; }
double Ride::getDistance() const { return distance; }
double Ride::getFare() const { return fare; }
std::time_t Ride::getRequestTime() const { return requestTime; }
std::time_t Ride::getCompletionTime() const { return completionTime; }
RideStatus Ride::getStatus() const { return status; }

void Ride::assignDriver(User* driver) {
    if (driver && driver->getType() == UserType::DRIVER) {
        this->driver = driver;
        status = RideStatus::ACCEPTED;
    }
}

void Ride::calculateFare() {
    // Simple fare calculation: base fare + distance-based fare
    const double BASE_FARE = 5.0;
    const double RATE_PER_KM = 2.0;
    fare = BASE_FARE + (distance * RATE_PER_KM);
}

void Ride::updateStatus(RideStatus status) {
    this->status = status;
    if (status == RideStatus::COMPLETED) {
        completionTime = std::time(nullptr);
        calculateFare();
    }
}

void Ride::displayInfo() const {
    std::cout << "\nRide Details:" << std::endl;
    std::cout << "ID: " << rideId << std::endl;
    std::cout << "Rider: " << rider->getName() << std::endl;
    if (driver) {
        std::cout << "Driver: " << driver->getName() << std::endl;
    }
    std::cout << "Status: ";
    switch (status) {
        case RideStatus::REQUESTED: std::cout << "Requested"; break;
        case RideStatus::ACCEPTED: std::cout << "Accepted"; break;
        case RideStatus::IN_PROGRESS: std::cout << "In Progress"; break;
        case RideStatus::COMPLETED: std::cout << "Completed"; break;
        case RideStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Pickup: " << pickup->getAddress() << std::endl;
    std::cout << "Dropoff: " << dropoff->getAddress() << std::endl;
    std::cout << "Distance: " << std::fixed << std::setprecision(2) << distance << " km" << std::endl;
    
    if (status == RideStatus::COMPLETED) {
        std::cout << "Fare: $" << std::fixed << std::setprecision(2) << fare << std::endl;
        std::cout << "Request Time: " << std::ctime(&requestTime);
        std::cout << "Completion Time: " << std::ctime(&completionTime);
    }
} 