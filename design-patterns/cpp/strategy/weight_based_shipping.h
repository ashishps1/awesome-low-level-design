#pragma once
#include "shipping_strategy.h"

class WeightBasedShipping : public ShippingStrategy {
public:
    double calculateCost(const Order& order) override;
}; 