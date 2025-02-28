#include "ATM.hpp"
#include <iostream>

int main() {
    ATM atm;
    
    // Create some test accounts
    Account* account1 = new Account("1234", "5678", 1000.0);
    Account* account2 = new Account("4321", "8765", 2000.0);
    
    // Add accounts to ATM
    atm.addAccount(account1);
    atm.addAccount(account2);
    
    // Start the ATM
    atm.start();
    
    return 0;
} 