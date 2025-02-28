#ifndef BROKERAGE_SYSTEM_HPP
#define BROKERAGE_SYSTEM_HPP

#include <vector>
#include <map>
#include <string>
#include "User.hpp"
#include "Stock.hpp"
#include "Transaction.hpp"

class BrokerageSystem {
private:
    std::vector<User*> users;
    std::map<std::string, Stock*> stocks;  // symbol -> Stock*
    std::vector<Transaction*> transactions;
    int transactionIdCounter;

public:
    BrokerageSystem();
    ~BrokerageSystem();
    
    // User management
    User* registerUser(const std::string& username, const std::string& email);
    void removeUser(const std::string& userId);
    
    // Stock management
    Stock* addStock(const std::string& symbol, const std::string& companyName,
                   double price, int shares);
    void updateStockPrice(const std::string& symbol, double newPrice);
    
    // Trading operations
    bool deposit(const std::string& userId, double amount);
    bool withdraw(const std::string& userId, double amount);
    Transaction* buyStock(const std::string& userId, const std::string& symbol, int quantity);
    Transaction* sellStock(const std::string& userId, const std::string& symbol, int quantity);
    
    // Display functions
    void displayStocks() const;
    void displayUsers() const;
    void displayUserPortfolio(const std::string& userId) const;
    void displayTransactionHistory(const std::string& userId) const;
    
private:
    User* findUser(const std::string& userId) const;
    Stock* findStock(const std::string& symbol) const;
    void updatePortfolioValues();
    std::string generateTransactionId();
};

#endif 