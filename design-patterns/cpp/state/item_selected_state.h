#pragma once
#include "machine_state.h"

class ItemSelectedState : public MachineState {
public:
    void selectItem(VendingMachine& context, const std::string& itemCode) override;
    void insertCoin(VendingMachine& context, double amount) override;
    void dispenseItem(VendingMachine& context) override;
}; 