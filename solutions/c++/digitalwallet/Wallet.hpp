#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

class Wallet {
private:
    std::string walletId;
    std::string userId;
    double balance;
    std::vector<Transaction*> transactions;

public:
    Wallet(std::string walletId, std::string userId);
    ~Wallet();
    
    std::string getWalletId() const;
    std::string getUserId() const;
    double getBalance() const;
    
    bool addMoney(double amount, std::string source);
    bool withdrawMoney(double amount, std::string destination);
    void addTransaction(Transaction* transaction);
    void displayInfo() const;
    void displayTransactions() const;
};

#endif 