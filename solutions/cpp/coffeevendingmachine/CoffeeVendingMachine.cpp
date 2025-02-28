#include "CoffeeVendingMachine.hpp"
#include <iostream>
#include <iomanip>

CoffeeVendingMachine::CoffeeVendingMachine() : moneyCollected(0.0) {
    initializeMenu();
}

void CoffeeVendingMachine::initializeMenu() {
    coffeeMenu.push_back(Coffee(CoffeeType::ESPRESSO, 2.50, "Strong black coffee"));
    coffeeMenu.push_back(Coffee(CoffeeType::LATTE, 3.50, "Coffee with steamed milk"));
    coffeeMenu.push_back(Coffee(CoffeeType::CAPPUCCINO, 3.00, "Coffee topped with foamy milk"));
    coffeeMenu.push_back(Coffee(CoffeeType::AMERICANO, 2.00, "Diluted espresso"));
}

void CoffeeVendingMachine::displayMenu() const {
    std::cout << "\nCoffee Menu:" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    for (const auto& coffee : coffeeMenu) {
        std::cout << "Type: ";
        switch (coffee.getType()) {
            case CoffeeType::ESPRESSO: std::cout << "Espresso"; break;
            case CoffeeType::LATTE: std::cout << "Latte"; break;
            case CoffeeType::CAPPUCCINO: std::cout << "Cappuccino"; break;
            case CoffeeType::AMERICANO: std::cout << "Americano"; break;
        }
        std::cout << " - $" << coffee.getPrice() << std::endl;
        std::cout << "Description: " << coffee.getDescription() << std::endl;
        std::cout << "Available: " << inventory.getQuantity(coffee.getType()) << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

bool CoffeeVendingMachine::selectCoffee(CoffeeType type, double payment) {
    Coffee* coffee = findCoffee(type);
    if (!coffee) {
        std::cout << "Invalid coffee selection!" << std::endl;
        return false;
    }
    
    if (!inventory.hasItem(type)) {
        std::cout << "Sorry, this coffee is out of stock!" << std::endl;
        return false;
    }
    
    if (payment < coffee->getPrice()) {
        std::cout << "Insufficient payment! Price is $" << coffee->getPrice() << std::endl;
        return false;
    }
    
    inventory.deductItem(type);
    moneyCollected += coffee->getPrice();
    double change = payment - coffee->getPrice();
    
    std::cout << "\nDispensing " << coffee->getDescription() << std::endl;
    if (change > 0) {
        std::cout << "Change: $" << std::fixed << std::setprecision(2) << change << std::endl;
    }
    
    return true;
}

void CoffeeVendingMachine::refillInventory(CoffeeType type, int quantity) {
    inventory.addItem(type, quantity);
    std::cout << "Inventory refilled successfully!" << std::endl;
}

double CoffeeVendingMachine::getMoneyCollected() const {
    return moneyCollected;
}

void CoffeeVendingMachine::displayInventory() const {
    inventory.display();
}

Coffee* CoffeeVendingMachine::findCoffee(CoffeeType type) {
    for (auto& coffee : coffeeMenu) {
        if (coffee.getType() == type) {
            return &coffee;
        }
    }
    return nullptr;
} 