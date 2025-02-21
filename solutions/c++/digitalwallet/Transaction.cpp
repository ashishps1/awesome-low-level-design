#include "Transaction.hpp"
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string transactionId, std::string walletId, 
                       TransactionType type, double amount, std::string timestamp,
                       std::string description)
    : transactionId(transactionId), walletId(walletId), type(type), 
      amount(amount), timestamp(timestamp), description(description), status(false) {}

std::string Transaction::getTransactionId() const { return transactionId; }
std::string Transaction::getWalletId() const { return walletId; }
TransactionType Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getTimestamp() const { return timestamp; }
std::string Transaction::getDescription() const { return description; }
bool Transaction::getStatus() const { return status; }

void Transaction::setStatus(bool status) {
    this->status = status;
}

void Transaction::displayInfo() const {
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case TransactionType::ADD_MONEY: std::cout << "Add Money"; break;
        case TransactionType::WITHDRAW: std::cout << "Withdraw"; break;
        case TransactionType::TRANSFER: std::cout << "Transfer"; break;
    }
    std::cout << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "Time: " << timestamp << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << (status ? "Success" : "Pending") << std::endl;
} 