#include "vending_machine.h"
#include "idle_state.h"

VendingMachine::VendingMachine()
    : currentState(std::make_unique<IdleState>())
    , selectedItem("")
    , insertedAmount(0.0) {}

void VendingMachine::setState(std::unique_ptr<MachineState> newState) {
    currentState = std::move(newState);
}

void VendingMachine::setSelectedItem(const std::string& itemCode) {
    selectedItem = itemCode;
}

void VendingMachine::setInsertedAmount(double amount) {
    insertedAmount = amount;
}

const std::string& VendingMachine::getSelectedItem() const {
    return selectedItem;
}

double VendingMachine::getInsertedAmount() const {
    return insertedAmount;
}

void VendingMachine::selectItem(const std::string& itemCode) {
    currentState->selectItem(*this, itemCode);
}

void VendingMachine::insertCoin(double amount) {
    currentState->insertCoin(*this, amount);
}

void VendingMachine::dispenseItem() {
    currentState->dispenseItem(*this);
}

void VendingMachine::reset() {
    selectedItem = "";
    insertedAmount = 0.0;
    currentState = std::make_unique<IdleState>();
} 