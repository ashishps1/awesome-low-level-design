#pragma once
#include "shipping_strategy.h"
#include <memory>

class ShippingCostService {
public:
    explicit ShippingCostService(std::unique_ptr<ShippingStrategy> strategy);
    void setStrategy(std::unique_ptr<ShippingStrategy> strategy);
    double calculateShippingCost(const Order& order);

private:
    std::unique_ptr<ShippingStrategy> strategy;
}; 