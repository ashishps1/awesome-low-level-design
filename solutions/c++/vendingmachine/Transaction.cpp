#include "Transaction.hpp"
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string transactionId, std::string productId, int quantity, double amount)
    : transactionId(transactionId), productId(productId), quantity(quantity), amount(amount),
      successful(false) {
    timestamp = std::time(nullptr);
}

std::string Transaction::getTransactionId() const { return transactionId; }
std::string Transaction::getProductId() const { return productId; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
bool Transaction::isSuccessful() const { return successful; }

void Transaction::setSuccessful(bool status) {
    successful = status;
}

void Transaction::displayInfo() const {
    std::cout << "Transaction " << transactionId << ":" << std::endl;
    std::cout << "Product ID: " << productId << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "Status: " << (successful ? "Successful" : "Failed") << std::endl;
    std::cout << "Time: " << std::ctime(&timestamp);
} 