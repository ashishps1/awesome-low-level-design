#include "Inventory.hpp"
#include <iostream>

Inventory::Inventory() {
    // Initialize inventory with zero quantity for all coffee types
    items[CoffeeType::ESPRESSO] = 0;
    items[CoffeeType::LATTE] = 0;
    items[CoffeeType::CAPPUCCINO] = 0;
    items[CoffeeType::AMERICANO] = 0;
}

void Inventory::addItem(CoffeeType type, int quantity) {
    items[type] += quantity;
}

bool Inventory::hasItem(CoffeeType type) {
    return items[type] > 0;
}

void Inventory::deductItem(CoffeeType type) {
    if (items[type] > 0) {
        items[type]--;
    }
}

int Inventory::getQuantity(CoffeeType type) const {
    auto it = items.find(type);
    return it != items.end() ? it->second : 0;
}

void Inventory::display() const {
    std::cout << "\nCurrent Inventory:" << std::endl;
    std::cout << "Espresso: " << items.at(CoffeeType::ESPRESSO) << std::endl;
    std::cout << "Latte: " << items.at(CoffeeType::LATTE) << std::endl;
    std::cout << "Cappuccino: " << items.at(CoffeeType::CAPPUCCINO) << std::endl;
    std::cout << "Americano: " << items.at(CoffeeType::AMERICANO) << std::endl;
} 