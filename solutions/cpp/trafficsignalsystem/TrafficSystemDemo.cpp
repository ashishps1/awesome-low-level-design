#include "TrafficSystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    TrafficSystem system;
    
    // Create an intersection
    Intersection* intersection1 = system.createIntersection();
    
    // Add signals to the intersection
    Signal* signal1 = system.addSignal(intersection1->getIntersectionId(), 20, 5, 25);
    Signal* signal2 = system.addSignal(intersection1->getIntersectionId(), 20, 5, 25);
    
    // Display initial status
    system.displaySystemStatus();
    
    // Simulate traffic system for a few cycles
    for (int i = 0; i < 10; i++) {
        std::cout << "\nTime step " << i + 1 << ":" << std::endl;
        system.updateSystem(5);  // Update every 5 seconds
        system.displaySystemStatus();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Simulate intersection failure
    std::cout << "\nSimulating intersection failure..." << std::endl;
    system.setIntersectionStatus(intersection1->getIntersectionId(), false);
    system.displaySystemStatus();
    
    // Restore intersection
    std::cout << "\nRestoring intersection..." << std::endl;
    system.setIntersectionStatus(intersection1->getIntersectionId(), true);
    system.synchronizeIntersection(intersection1->getIntersectionId());
    system.displaySystemStatus();
    
    return 0;
} 