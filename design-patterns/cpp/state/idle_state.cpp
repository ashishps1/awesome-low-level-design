#include "idle_state.h"
#include "vending_machine.h"
#include "item_selected_state.h"
#include <iostream>

void IdleState::selectItem(VendingMachine& context, const std::string& itemCode) {
    std::cout << "Item selected: " << itemCode << std::endl;
    context.setSelectedItem(itemCode);
    context.setState(std::make_unique<ItemSelectedState>());
}

void IdleState::insertCoin(VendingMachine& context, double amount) {
    std::cout << "Please select an item first." << std::endl;
}

void IdleState::dispenseItem(VendingMachine& context) {
    std::cout << "Please select an item first." << std::endl;
} 