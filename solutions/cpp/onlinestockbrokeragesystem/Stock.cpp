#include "Stock.hpp"
#include <iostream>
#include <iomanip>

Stock::Stock(std::string symbol, std::string companyName, double currentPrice, int availableShares)
    : symbol(symbol), companyName(companyName), currentPrice(currentPrice), 
      availableShares(availableShares), active(true) {}

std::string Stock::getSymbol() const { return symbol; }
std::string Stock::getCompanyName() const { return companyName; }
double Stock::getCurrentPrice() const { return currentPrice; }
int Stock::getAvailableShares() const { return availableShares; }
bool Stock::isActive() const { return active; }

void Stock::setCurrentPrice(double price) {
    if (price > 0) {
        currentPrice = price;
    }
}

void Stock::updateShares(int quantity) {
    if (availableShares + quantity >= 0) {
        availableShares += quantity;
        active = (availableShares > 0);
    }
}

void Stock::setActive(bool status) {
    active = status;
}

void Stock::displayInfo() const {
    std::cout << "Stock: " << companyName << " (" << symbol << ")" << std::endl;
    std::cout << "Current Price: $" << std::fixed << std::setprecision(2) << currentPrice << std::endl;
    std::cout << "Available Shares: " << availableShares << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
} 