#include "flat_rate_shipping.h"
#include <iostream>

double FlatRateShipping::calculateCost(const Order& order) {
    std::cout << "Calculating flat rate shipping cost..." << std::endl;
    return 10.0; // Fixed rate of $10
} 