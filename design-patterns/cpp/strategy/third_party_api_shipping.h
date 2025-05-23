#pragma once
#include "shipping_strategy.h"

class ThirdPartyApiShipping : public ShippingStrategy {
public:
    double calculateCost(const Order& order) override;
}; 