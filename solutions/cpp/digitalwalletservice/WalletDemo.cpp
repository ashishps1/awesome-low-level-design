#include "WalletSystem.hpp"
#include <iostream>

int main() {
    WalletSystem system;
    
    // Create users
    User* user1 = new User("U001", "John Doe", "john@example.com", "+1-555-0123");
    User* user2 = new User("U002", "Jane Smith", "jane@example.com", "+1-555-0124");
    
    system.addUser(user1);
    system.addUser(user2);
    
    // Create wallets
    Wallet* wallet1 = system.createWallet("U001");
    Wallet* wallet2 = system.createWallet("U002");
    
    // Add money to wallets
    if (system.addMoney("WU001", 1000.0, "Bank Transfer")) {
        std::cout << "Added $1000 to John's wallet" << std::endl;
    }
    
    if (system.addMoney("WU002", 500.0, "Credit Card")) {
        std::cout << "Added $500 to Jane's wallet" << std::endl;
    }
    
    // Transfer money
    if (system.transferMoney("WU001", "WU002", 300.0)) {
        std::cout << "Transferred $300 from John to Jane" << std::endl;
    }
    
    // Withdraw money
    if (system.withdrawMoney("WU002", 200.0, "Bank Account")) {
        std::cout << "Jane withdrew $200" << std::endl;
    }
    
    // Display information
    system.displayAllUsers();
    system.displayAllWallets();
    
    // Display detailed user information
    std::cout << "\nDetailed User Information:" << std::endl;
    system.displayUserInfo("U001");
    
    return 0;
} 