#ifndef WALLET_SYSTEM_HPP
#define WALLET_SYSTEM_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Wallet.hpp"
#include "Transaction.hpp"

class WalletSystem {
private:
    std::vector<User*> users;
    std::vector<Wallet*> wallets;
    int transactionIdCounter;

public:
    WalletSystem();
    ~WalletSystem();
    
    void addUser(User* user);
    Wallet* createWallet(std::string userId);
    
    bool addMoney(std::string walletId, double amount, std::string source);
    bool withdrawMoney(std::string walletId, double amount, std::string destination);
    bool transferMoney(std::string fromWalletId, std::string toWalletId, double amount);
    
    void displayUserInfo(std::string userId) const;
    void displayWalletInfo(std::string walletId) const;
    void displayAllUsers() const;
    void displayAllWallets() const;
    
private:
    User* findUser(const std::string& userId) const;
    Wallet* findWallet(const std::string& walletId) const;
    std::string generateTransactionId();
    std::string getCurrentTimestamp() const;
};

#endif 