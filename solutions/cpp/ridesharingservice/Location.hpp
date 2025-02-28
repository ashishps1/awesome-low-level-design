#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

class Location {
private:
    double latitude;
    double longitude;
    std::string address;

public:
    Location(double latitude, double longitude, std::string address);
    
    double getLatitude() const;
    double getLongitude() const;
    std::string getAddress() const;
    
    double calculateDistance(const Location& other) const;
    void displayInfo() const;
};

#endif 