#ifndef PARKING_LOT_HPP
#define PARKING_LOT_HPP

#include <vector>
#include <map>
#include <string>
#include "ParkingSpot.hpp"
#include "ParkingTicket.hpp"
#include "FeeFlatRate.hpp"
#include "FeeVehicleBased.hpp"

class ParkingLot {
private:
    std::vector<ParkingSpot*> spots;
    std::map<std::string, ParkingSpot*> occupiedSpots;  // licensePlate -> spot
    std::map<ParkingSpot*, ParkingTicket*> activeTickets;    // ParkingSpot* -> ticket
    int capacity;
    int availableSpots;
    FeeStrategy* feeStrategy;

public:
    ParkingLot(int numCompact, int numRegular, int numLarge, FeeStrategy* feeStrategy);
    ~ParkingLot();
    
    int getCapacity() const;
    int getAvailableSpots() const;
    
    bool parkVehicle(Vehicle* vehicle);
    Vehicle* removeVehicle(const std::string& licensePlate);
    ParkingSpot* findVehicle(const std::string& licensePlate) const;
    
    void displayInfo() const;
    void displayOccupancy() const;
    void displayFee(ParkingTicket* ticket);
private:
    ParkingSpot* findAvailableSpot(const Vehicle* vehicle) const;
};

#endif 