#include "Location.hpp"
#include <iostream>
#include <cmath>

Location::Location(double latitude, double longitude, std::string address)
    : latitude(latitude), longitude(longitude), address(address) {}

double Location::getLatitude() const { return latitude; }
double Location::getLongitude() const { return longitude; }
std::string Location::getAddress() const { return address; }

double Location::calculateDistance(const Location& other) const {
    // Simple Euclidean distance for demonstration
    double dx = latitude - other.latitude;
    double dy = longitude - other.longitude;
    return std::sqrt(dx * dx + dy * dy);
}

void Location::displayInfo() const {
    std::cout << "Location: " << address << std::endl;
    std::cout << "Coordinates: (" << latitude << ", " << longitude << ")" << std::endl;
} 