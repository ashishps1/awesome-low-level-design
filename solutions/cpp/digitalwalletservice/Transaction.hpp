#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

enum class TransactionType {
    ADD_MONEY,
    WITHDRAW,
    TRANSFER
};

class Transaction {
private:
    std::string transactionId;
    std::string walletId;
    TransactionType type;
    double amount;
    std::string timestamp;
    std::string description;
    bool status;

public:
    Transaction(std::string transactionId, std::string walletId, 
               TransactionType type, double amount, std::string timestamp,
               std::string description);
    
    std::string getTransactionId() const;
    std::string getWalletId() const;
    TransactionType getType() const;
    double getAmount() const;
    std::string getTimestamp() const;
    std::string getDescription() const;
    bool getStatus() const;
    
    void setStatus(bool status);
    void displayInfo() const;
};

#endif 