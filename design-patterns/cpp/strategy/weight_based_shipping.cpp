#include "weight_based_shipping.h"
#include <iostream>

double WeightBasedShipping::calculateCost(const Order& order) {
    std::cout << "Calculating weight-based shipping cost..." << std::endl;
    return order.getTotalWeight() * 2.0; // $2 per kg
} 