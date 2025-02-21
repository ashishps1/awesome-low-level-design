#ifndef PARKING_SPOT_HPP
#define PARKING_SPOT_HPP

#include "Vehicle.hpp"

enum class SpotType {
    COMPACT,
    REGULAR,
    LARGE
};

class ParkingSpot {
private:
    int spotNumber;
    SpotType type;
    Vehicle* vehicle;
    bool available;

public:
    ParkingSpot(int spotNumber, SpotType type);
    
    int getSpotNumber() const;
    SpotType getType() const;
    Vehicle* getVehicle() const;
    bool isAvailable() const;
    
    bool canFitVehicle(const Vehicle* vehicle) const;
    bool parkVehicle(Vehicle* vehicle);
    Vehicle* removeVehicle();
    void displayInfo() const;
};

#endif 