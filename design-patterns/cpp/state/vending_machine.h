#pragma once
#include "machine_state.h"
#include <memory>
#include <string>

class VendingMachine {
public:
    VendingMachine();
    
    void setState(std::unique_ptr<MachineState> newState);
    void setSelectedItem(const std::string& itemCode);
    void setInsertedAmount(double amount);
    
    const std::string& getSelectedItem() const;
    double getInsertedAmount() const;
    
    void selectItem(const std::string& itemCode);
    void insertCoin(double amount);
    void dispenseItem();
    void reset();

private:
    std::unique_ptr<MachineState> currentState;
    std::string selectedItem;
    double insertedAmount;
}; 