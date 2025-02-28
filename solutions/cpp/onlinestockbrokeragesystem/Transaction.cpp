#include "Transaction.hpp"
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string transactionId, User* user, Stock* stock,
                       TransactionType type, int quantity, double pricePerShare)
    : transactionId(transactionId), user(user), stock(stock), type(type),
      quantity(quantity), pricePerShare(pricePerShare) {
    totalAmount = quantity * pricePerShare;
    timestamp = std::time(nullptr);
}

std::string Transaction::getTransactionId() const { return transactionId; }
User* Transaction::getUser() const { return user; }
Stock* Transaction::getStock() const { return stock; }
TransactionType Transaction::getType() const { return type; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getPricePerShare() const { return pricePerShare; }
double Transaction::getTotalAmount() const { return totalAmount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }

void Transaction::displayInfo() const {
    std::cout << "\nTransaction Details:" << std::endl;
    std::cout << "ID: " << transactionId << std::endl;
    std::cout << "Type: " << (type == TransactionType::BUY ? "Buy" : "Sell") << std::endl;
    std::cout << "Stock: " << stock->getSymbol() << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Price per Share: $" << std::fixed << std::setprecision(2) << pricePerShare << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    std::cout << "Time: " << std::ctime(&timestamp);
} 