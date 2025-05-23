#pragma once
#include "shipping_strategy.h"

class FlatRateShipping : public ShippingStrategy {
public:
    double calculateCost(const Order& order) override;
}; 