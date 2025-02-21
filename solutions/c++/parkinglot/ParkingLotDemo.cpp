#include "ParkingLot.hpp"
#include <iostream>

int main() {
    // Create parking lot with different types of spots
    ParkingLot parkingLot(2, 3, 2);  // 2 compact, 3 regular, 2 large spots
    
    std::cout << "Initial parking lot status:" << std::endl;
    parkingLot.displayInfo();
    
    // Create vehicles
    Vehicle* car1 = new Vehicle("CAR001", VehicleType::CAR, "Red");
    Vehicle* car2 = new Vehicle("CAR002", VehicleType::CAR, "Blue");
    Vehicle* motorcycle = new Vehicle("MOTO001", VehicleType::MOTORCYCLE, "Black");
    Vehicle* truck = new Vehicle("TRUCK001", VehicleType::TRUCK, "White");
    
    // Park vehicles
    std::cout << "\nParking vehicles..." << std::endl;
    
    if (parkingLot.parkVehicle(car1)) {
        std::cout << "Parked successfully: ";
        car1->displayInfo();
    }
    
    if (parkingLot.parkVehicle(motorcycle)) {
        std::cout << "Parked successfully: ";
        motorcycle->displayInfo();
    }
    
    if (parkingLot.parkVehicle(truck)) {
        std::cout << "Parked successfully: ";
        truck->displayInfo();
    }
    
    // Display current status
    parkingLot.displayInfo();
    parkingLot.displayOccupancy();
    
    // Remove a vehicle
    std::cout << "\nRemoving vehicle CAR001..." << std::endl;
    Vehicle* removed = parkingLot.removeVehicle("CAR001");
    if (removed) {
        std::cout << "Removed successfully: ";
        removed->displayInfo();
        delete removed;
    }
    
    // Try to park another car
    if (parkingLot.parkVehicle(car2)) {
        std::cout << "Parked successfully: ";
        car2->displayInfo();
    }
    
    // Final status
    std::cout << "\nFinal parking lot status:" << std::endl;
    parkingLot.displayInfo();
    parkingLot.displayOccupancy();
    
    // Cleanup remaining vehicles
    delete car2;
    delete motorcycle;
    delete truck;
    
    return 0;
} 