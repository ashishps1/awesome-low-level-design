#include "BrokerageSystem.hpp"
#include <iostream>

int main() {
    BrokerageSystem brokerage;
    
    // Add stocks
    Stock* apple = brokerage.addStock("AAPL", "Apple Inc.", 150.0, 1000);
    Stock* google = brokerage.addStock("GOOGL", "Alphabet Inc.", 2800.0, 500);
    Stock* amazon = brokerage.addStock("AMZN", "Amazon.com Inc.", 3300.0, 300);
    
    std::cout << "Initial Stocks:" << std::endl;
    brokerage.displayStocks();
    
    // Register users
    User* user1 = brokerage.registerUser("john_trader", "john@email.com");
    User* user2 = brokerage.registerUser("jane_investor", "jane@email.com");
    
    // Deposit funds
    brokerage.deposit(user1->getUserId(), 10000.0);
    brokerage.deposit(user2->getUserId(), 15000.0);
    
    std::cout << "\nUsers after deposit:" << std::endl;
    brokerage.displayUsers();
    
    // Perform transactions
    Transaction* trans1 = brokerage.buyStock(user1->getUserId(), "AAPL", 10);
    if (trans1) {
        std::cout << "\nBuy Transaction:" << std::endl;
        trans1->displayInfo();
    }
    
    // Update stock price
    brokerage.updateStockPrice("AAPL", 155.0);
    
    Transaction* trans2 = brokerage.sellStock(user1->getUserId(), "AAPL", 5);
    if (trans2) {
        std::cout << "\nSell Transaction:" << std::endl;
        trans2->displayInfo();
    }
    
    // Display final state
    std::cout << "\nFinal Portfolio for John:" << std::endl;
    brokerage.displayUserPortfolio(user1->getUserId());
    
    std::cout << "\nTransaction History for John:" << std::endl;
    brokerage.displayTransactionHistory(user1->getUserId());
    
    return 0;
} 