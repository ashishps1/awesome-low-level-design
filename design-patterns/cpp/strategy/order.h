#pragma once
#include <string>

class Order {
public:
    double getTotalWeight() const { return 5.0; } // kg
    std::string getDestinationZone() const { return "ZoneA"; }
    double getOrderValue() const { return 150.0; }
    // ... other order details
}; 