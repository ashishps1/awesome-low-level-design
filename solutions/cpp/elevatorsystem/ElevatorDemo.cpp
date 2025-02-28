#include "ElevatorSystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    ElevatorSystem system(2, 10); // 2 elevators, 10 floors
    
    // Add some requests
    system.addRequest(0, Request(0, 5));  // Elevator 0: Ground floor to 5th floor
    system.addRequest(1, Request(2, 7));  // Elevator 1: 2nd floor to 7th floor
    system.addRequest(0, Request(5, 3));  // Elevator 0: 5th floor to 3rd floor
    
    // Simulate elevator movement
    for (int i = 0; i < 15; i++) {
        system.displayStatus();
        system.step();
        
        // Wait for a second before next step
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
} 