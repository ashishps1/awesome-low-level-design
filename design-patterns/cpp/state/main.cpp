#include "vending_machine.h"
#include <iostream>

int main() {
    VendingMachine machine;

    // Test the vending machine workflow
    std::cout << "=== Vending Machine Demo ===\n" << std::endl;

    // Try to insert coin before selecting item
    std::cout << "Attempting to insert coin before selecting item:" << std::endl;
    machine.insertCoin(1.0);

    // Select an item
    std::cout << "\nSelecting item A1:" << std::endl;
    machine.selectItem("A1");

    // Insert coin
    std::cout << "\nInserting coin:" << std::endl;
    machine.insertCoin(1.0);

    // Try to select another item
    std::cout << "\nAttempting to select another item:" << std::endl;
    machine.selectItem("B2");

    // Insert more money
    std::cout << "\nInserting more money:" << std::endl;
    machine.insertCoin(0.5);

    // Dispense item
    std::cout << "\nDispensing item:" << std::endl;
    machine.dispenseItem();

    // Try to interact after dispensing
    std::cout << "\nAttempting to interact after dispensing:" << std::endl;
    machine.selectItem("C3");
    machine.insertCoin(1.0);
    machine.dispenseItem();

    return 0;
} 