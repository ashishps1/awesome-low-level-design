#include "shipping_cost_service.h"

ShippingCostService::ShippingCostService(std::unique_ptr<ShippingStrategy> strategy)
    : strategy(std::move(strategy)) {}

void ShippingCostService::setStrategy(std::unique_ptr<ShippingStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

double ShippingCostService::calculateShippingCost(const Order& order) {
    return strategy->calculateCost(order);
} 