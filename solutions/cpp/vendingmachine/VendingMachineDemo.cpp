#include "VendingMachine.hpp"
#include <iostream>

int main() {
    VendingMachine machine("VM001");
    
    // Add products
    Product* cola = machine.addProduct("Cola", 2.50, 10);
    Product* chips = machine.addProduct("Chips", 1.50, 15);
    Product* candy = machine.addProduct("Candy", 1.00, 20);
    
    // Display initial inventory
    std::cout << "Initial machine status:" << std::endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    // Make some purchases
    std::cout << "\nMaking purchases..." << std::endl;
    Transaction* t1 = machine.purchaseProduct(cola->getProductId(), 2, 5.00);
    Transaction* t2 = machine.purchaseProduct(chips->getProductId(), 3, 5.00);
    
    // Display transactions
    machine.displayTransactions();
    
    // Restock a product
    std::cout << "\nRestocking Cola..." << std::endl;
    machine.restockProduct(cola->getProductId(), 5);
    
    // Update price
    std::cout << "\nUpdating Candy price..." << std::endl;
    machine.updatePrice(candy->getProductId(), 1.25);
    
    // Display final status
    std::cout << "\nFinal machine status:" << std::endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    return 0;
} 