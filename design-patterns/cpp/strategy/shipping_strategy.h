#pragma once
#include "order.h"

class ShippingStrategy {
public:
    virtual ~ShippingStrategy() = default;
    virtual double calculateCost(const Order& order) = 0;
}; 