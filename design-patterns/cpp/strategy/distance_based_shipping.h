#pragma once
#include "shipping_strategy.h"

class DistanceBasedShipping : public ShippingStrategy {
public:
    double calculateCost(const Order& order) override;
}; 