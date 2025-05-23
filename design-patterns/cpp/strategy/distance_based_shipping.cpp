#include "distance_based_shipping.h"
#include <iostream>
#include <map>

double DistanceBasedShipping::calculateCost(const Order& order) {
    std::cout << "Calculating distance-based shipping cost..." << std::endl;
    
    // Zone-based rates
    std::map<std::string, double> zoneRates = {
        {"ZoneA", 5.0},
        {"ZoneB", 10.0},
        {"ZoneC", 15.0}
    };

    auto it = zoneRates.find(order.getDestinationZone());
    if (it != zoneRates.end()) {
        return it->second;
    }
    return 20.0; // Default rate for unknown zones
} 