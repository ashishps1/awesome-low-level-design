#include "dispensing_state.h"
#include "vending_machine.h"
#include "idle_state.h"
#include <iostream>

void DispensingState::selectItem(VendingMachine& context, const std::string& itemCode) {
    std::cout << "Please wait, item is being dispensed." << std::endl;
}

void DispensingState::insertCoin(VendingMachine& context, double amount) {
    std::cout << "Please wait, item is being dispensed." << std::endl;
}

void DispensingState::dispenseItem(VendingMachine& context) {
    std::cout << "Item dispensed. Thank you for your purchase!" << std::endl;
    context.reset();
    context.setState(std::make_unique<IdleState>());
} 