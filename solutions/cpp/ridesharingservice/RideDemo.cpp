#include "RideService.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    RideService service;
    
    // Register users
    User* rider1 = service.registerUser("John", "123-456-7890", UserType::RIDER,
        new Location(40.7128, -74.0060, "New York City"));
    
    User* rider2 = service.registerUser("Alice", "123-456-7891", UserType::RIDER,
        new Location(34.0522, -118.2437, "Los Angeles"));
    
    User* driver1 = service.registerUser("Bob", "123-456-7892", UserType::DRIVER,
        new Location(40.7300, -74.0100, "Near NYC"));
    
    User* driver2 = service.registerUser("Carol", "123-456-7893", UserType::DRIVER,
        new Location(34.0500, -118.2400, "Near LA"));
    
    std::cout << "Initial users:" << std::endl;
    service.displayUsers();
    
    // Request rides
    Location* pickup1 = new Location(40.7128, -74.0060, "NYC Downtown");
    Location* dropoff1 = new Location(40.7589, -73.9851, "Central Park");
    
    std::cout << "\nRequesting ride..." << std::endl;
    Ride* ride1 = service.requestRide(rider1->getUserId(), pickup1, dropoff1);
    
    if (ride1) {
        std::cout << "Ride requested successfully:" << std::endl;
        ride1->displayInfo();
        
        // Update ride status
        std::cout << "\nUpdating ride status..." << std::endl;
        service.updateRideStatus(ride1->getRideId(), RideStatus::IN_PROGRESS);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        service.updateRideStatus(ride1->getRideId(), RideStatus::COMPLETED);
        
        // Rate users
        std::cout << "\nRating users..." << std::endl;
        service.rateUser(ride1->getDriver()->getUserId(), 5.0);  // Rate driver
        service.rateUser(ride1->getRider()->getUserId(), 4.5);   // Rate rider
    }
    
    // Display final status
    std::cout << "\nFinal user status:" << std::endl;
    service.displayUsers();
    
    std::cout << "\nRide history:" << std::endl;
    service.displayRides();
    
    return 0;
} 