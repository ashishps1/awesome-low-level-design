#include "third_party_api_shipping.h"
#include <iostream>

double ThirdPartyApiShipping::calculateCost(const Order& order) {
    std::cout << "Calculating shipping cost using third-party API..." << std::endl;
    // Simulate API call
    return order.getOrderValue() * 0.1; // 10% of order value
} 