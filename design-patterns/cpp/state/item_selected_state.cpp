#include "item_selected_state.h"
#include "vending_machine.h"
#include "has_money_state.h"
#include <iostream>

void ItemSelectedState::selectItem(VendingMachine& context, const std::string& itemCode) {
    std::cout << "Item already selected. Please insert money or cancel." << std::endl;
}

void ItemSelectedState::insertCoin(VendingMachine& context, double amount) {
    std::cout << "Money inserted: $" << amount << std::endl;
    context.setInsertedAmount(amount);
    context.setState(std::make_unique<HasMoneyState>());
}

void ItemSelectedState::dispenseItem(VendingMachine& context) {
    std::cout << "Please insert money first." << std::endl;
} 