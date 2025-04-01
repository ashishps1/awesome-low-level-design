#include "Portfolio.hpp"
#include <iostream>
#include <iomanip>

Portfolio::Portfolio(std::string userId) : userId(userId), totalValue(0.0) {}

std::string Portfolio::getUserId() const { return userId; }
const std::map<std::string, int>& Portfolio::getHoldings() const { return holdings; }
double Portfolio::getTotalValue() const { return totalValue; }

int Portfolio::getShareQuantity(const std::string& symbol) const {
    auto it = holdings.find(symbol);
    return it != holdings.end() ? it->second : 0;
}

void Portfolio::addShares(const std::string& symbol, int quantity) {
    if (quantity > 0) {
        holdings[symbol] += quantity;
    }
}

bool Portfolio::removeShares(const std::string& symbol, int quantity) {
    auto it = holdings.find(symbol);
    if (it != holdings.end() && it->second >= quantity) {
        it->second -= quantity;
        if (it->second == 0) {
            holdings.erase(it);
        }
        return true;
    }
    return false;
}

void Portfolio::updateTotalValue(const std::map<std::string, Stock*>& stocks) {
    totalValue = 0.0;
    for (const auto& holding : holdings) {
        auto stockIt = stocks.find(holding.first);
        if (stockIt != stocks.end()) {
            totalValue += stockIt->second->getCurrentPrice() * holding.second;
        }
    }
}

void Portfolio::displayInfo() const {
    std::cout << "\nPortfolio Holdings:" << std::endl;
    if (holdings.empty()) {
        std::cout << "No holdings" << std::endl;
    } else {
        for (const auto& holding : holdings) {
            std::cout << holding.first << ": " << holding.second << " shares" << std::endl;
        }
    }
    std::cout << "Total Value: $" << std::fixed << std::setprecision(2) << totalValue << std::endl;
} 