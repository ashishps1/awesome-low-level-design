#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>
#include "Stock.hpp"
#include "User.hpp"

enum class TransactionType {
    BUY,
    SELL
};

class Transaction {
private:
    std::string transactionId;
    User* user;
    Stock* stock;
    TransactionType type;
    int quantity;
    double pricePerShare;
    double totalAmount;
    std::time_t timestamp;

public:
    Transaction(std::string transactionId, User* user, Stock* stock,
               TransactionType type, int quantity, double pricePerShare);
    
    std::string getTransactionId() const;
    User* getUser() const;
    Stock* getStock() const;
    TransactionType getType() const;
    int getQuantity() const;
    double getPricePerShare() const;
    double getTotalAmount() const;
    std::time_t getTimestamp() const;
    
    void displayInfo() const;
};

#endif 