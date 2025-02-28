#ifndef PARKING_LOT_HPP
#define PARKING_LOT_HPP

#include <vector>
#include <map>
#include <string>
#include "ParkingSpot.hpp"

class ParkingLot {
private:
    std::vector<ParkingSpot*> spots;
    std::map<std::string, ParkingSpot*> occupiedSpots;  // licensePlate -> spot
    int capacity;
    int availableSpots;

public:
    ParkingLot(int numCompact, int numRegular, int numLarge);
    ~ParkingLot();
    
    int getCapacity() const;
    int getAvailableSpots() const;
    
    bool parkVehicle(Vehicle* vehicle);
    Vehicle* removeVehicle(const std::string& licensePlate);
    ParkingSpot* findVehicle(const std::string& licensePlate) const;
    
    void displayInfo() const;
    void displayOccupancy() const;

private:
    ParkingSpot* findAvailableSpot(const Vehicle* vehicle) const;
};

#endif 