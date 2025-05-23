#include "has_money_state.h"
#include "vending_machine.h"
#include "dispensing_state.h"
#include <iostream>

void HasMoneyState::selectItem(VendingMachine& context, const std::string& itemCode) {
    std::cout << "Item already selected. Please dispense current item or cancel." << std::endl;
}

void HasMoneyState::insertCoin(VendingMachine& context, double amount) {
    std::cout << "Additional money inserted: $" << amount << std::endl;
    context.setInsertedAmount(context.getInsertedAmount() + amount);
}

void HasMoneyState::dispenseItem(VendingMachine& context) {
    std::cout << "Dispensing item: " << context.getSelectedItem() << std::endl;
    context.setState(std::make_unique<DispensingState>());
} 