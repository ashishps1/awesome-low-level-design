#pragma once
#include <string>

class VendingMachine;  // Forward declaration

class MachineState {
public:
    virtual ~MachineState() = default;
    virtual void selectItem(VendingMachine& context, const std::string& itemCode) = 0;
    virtual void insertCoin(VendingMachine& context, double amount) = 0;
    virtual void dispenseItem(VendingMachine& context) = 0;
}; 