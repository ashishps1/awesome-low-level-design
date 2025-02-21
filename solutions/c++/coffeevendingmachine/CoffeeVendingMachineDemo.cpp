#include "CoffeeVendingMachine.hpp"
#include <iostream>

int main() {
    CoffeeVendingMachine machine;
    
    // Refill inventory
    machine.refillInventory(CoffeeType::ESPRESSO, 5);
    machine.refillInventory(CoffeeType::LATTE, 5);
    machine.refillInventory(CoffeeType::CAPPUCCINO, 5);
    machine.refillInventory(CoffeeType::AMERICANO, 5);
    
    // Display menu and inventory
    machine.displayMenu();
    machine.displayInventory();
    
    // Make some purchases
    std::cout << "\nMaking purchases:" << std::endl;
    
    if (machine.selectCoffee(CoffeeType::ESPRESSO, 3.00)) {
        std::cout << "Espresso purchased successfully!" << std::endl;
    }
    
    if (machine.selectCoffee(CoffeeType::LATTE, 3.50)) {
        std::cout << "Latte purchased successfully!" << std::endl;
    }
    
    // Try insufficient payment
    if (!machine.selectCoffee(CoffeeType::CAPPUCCINO, 2.00)) {
        std::cout << "Cappuccino purchase failed - insufficient payment" << std::endl;
    }
    
    // Display updated inventory and money collected
    machine.displayInventory();
    std::cout << "\nTotal money collected: $" << machine.getMoneyCollected() << std::endl;
    
    return 0;
} 