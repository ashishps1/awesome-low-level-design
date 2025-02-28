#include "ParkingLot.hpp"
#include <iostream>

ParkingLot::ParkingLot(int numCompact, int numRegular, int numLarge) 
    : capacity(numCompact + numRegular + numLarge), availableSpots(capacity) {
    
    int spotNumber = 1;
    
    // Create compact spots
    for (int i = 0; i < numCompact; i++) {
        spots.push_back(new ParkingSpot(spotNumber++, SpotType::COMPACT));
    }
    
    // Create regular spots
    for (int i = 0; i < numRegular; i++) {
        spots.push_back(new ParkingSpot(spotNumber++, SpotType::REGULAR));
    }
    
    // Create large spots
    for (int i = 0; i < numLarge; i++) {
        spots.push_back(new ParkingSpot(spotNumber++, SpotType::LARGE));
    }
}

ParkingLot::~ParkingLot() {
    for (auto spot : spots) {
        delete spot;
    }
}

int ParkingLot::getCapacity() const { return capacity; }
int ParkingLot::getAvailableSpots() const { return availableSpots; }

bool ParkingLot::parkVehicle(Vehicle* vehicle) {
    if (!vehicle) return false;
    
    // Check if vehicle is already parked
    if (occupiedSpots.find(vehicle->getLicensePlate()) != occupiedSpots.end()) {
        return false;
    }
    
    ParkingSpot* spot = findAvailableSpot(vehicle);
    if (!spot) return false;
    
    if (spot->parkVehicle(vehicle)) {
        occupiedSpots[vehicle->getLicensePlate()] = spot;
        availableSpots--;
        return true;
    }
    return false;
}

Vehicle* ParkingLot::removeVehicle(const std::string& licensePlate) {
    auto it = occupiedSpots.find(licensePlate);
    if (it == occupiedSpots.end()) return nullptr;
    
    ParkingSpot* spot = it->second;
    Vehicle* vehicle = spot->removeVehicle();
    if (vehicle) {
        occupiedSpots.erase(it);
        availableSpots++;
    }
    return vehicle;
}

ParkingSpot* ParkingLot::findVehicle(const std::string& licensePlate) const {
    auto it = occupiedSpots.find(licensePlate);
    return it != occupiedSpots.end() ? it->second : nullptr;
}

void ParkingLot::displayInfo() const {
    std::cout << "\nParking Lot Status:" << std::endl;
    std::cout << "Total Capacity: " << capacity << std::endl;
    std::cout << "Available Spots: " << availableSpots << std::endl;
    std::cout << "Occupied Spots: " << (capacity - availableSpots) << std::endl;
}

void ParkingLot::displayOccupancy() const {
    std::cout << "\nDetailed Occupancy:" << std::endl;
    for (const auto& spot : spots) {
        spot->displayInfo();
    }
}

ParkingSpot* ParkingLot::findAvailableSpot(const Vehicle* vehicle) const {
    for (auto spot : spots) {
        if (spot->isAvailable() && spot->canFitVehicle(vehicle)) {
            return spot;
        }
    }
    return nullptr;
} 