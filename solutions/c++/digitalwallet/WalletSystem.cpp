#include "WalletSystem.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

WalletSystem::WalletSystem() : transactionIdCounter(1) {}

WalletSystem::~WalletSystem() {
    for (auto user : users) delete user;
    for (auto wallet : wallets) delete wallet;
}

void WalletSystem::addUser(User* user) {
    users.push_back(user);
}

Wallet* WalletSystem::createWallet(std::string userId) {
    if (!findUser(userId)) return nullptr;
    
    std::string walletId = "W" + userId;
    Wallet* wallet = new Wallet(walletId, userId);
    wallets.push_back(wallet);
    return wallet;
}

bool WalletSystem::addMoney(std::string walletId, double amount, std::string source) {
    Wallet* wallet = findWallet(walletId);
    if (!wallet) return false;
    
    if (wallet->addMoney(amount, source)) {
        Transaction* transaction = new Transaction(
            generateTransactionId(),
            walletId,
            TransactionType::ADD_MONEY,
            amount,
            getCurrentTimestamp(),
            "Added money from " + source
        );
        transaction->setStatus(true);
        wallet->addTransaction(transaction);
        return true;
    }
    return false;
}

bool WalletSystem::withdrawMoney(std::string walletId, double amount, std::string destination) {
    Wallet* wallet = findWallet(walletId);
    if (!wallet) return false;
    
    if (wallet->withdrawMoney(amount, destination)) {
        Transaction* transaction = new Transaction(
            generateTransactionId(),
            walletId,
            TransactionType::WITHDRAW,
            amount,
            getCurrentTimestamp(),
            "Withdrawn to " + destination
        );
        transaction->setStatus(true);
        wallet->addTransaction(transaction);
        return true;
    }
    return false;
}

bool WalletSystem::transferMoney(std::string fromWalletId, std::string toWalletId, double amount) {
    Wallet* fromWallet = findWallet(fromWalletId);
    Wallet* toWallet = findWallet(toWalletId);
    if (!fromWallet || !toWallet) return false;
    
    if (fromWallet->withdrawMoney(amount, "Transfer to " + toWalletId) &&
        toWallet->addMoney(amount, "Transfer from " + fromWalletId)) {
        
        Transaction* transaction = new Transaction(
            generateTransactionId(),
            fromWalletId,
            TransactionType::TRANSFER,
            amount,
            getCurrentTimestamp(),
            "Transfer to wallet " + toWalletId
        );
        transaction->setStatus(true);
        fromWallet->addTransaction(transaction);
        
        transaction = new Transaction(
            generateTransactionId(),
            toWalletId,
            TransactionType::TRANSFER,
            amount,
            getCurrentTimestamp(),
            "Transfer from wallet " + fromWalletId
        );
        transaction->setStatus(true);
        toWallet->addTransaction(transaction);
        
        return true;
    }
    return false;
}

void WalletSystem::displayUserInfo(std::string userId) const {
    User* user = findUser(userId);
    if (user) {
        user->displayInfo();
        for (const auto& wallet : wallets) {
            if (wallet->getUserId() == userId) {
                wallet->displayInfo();
                wallet->displayTransactions();
            }
        }
    }
}

void WalletSystem::displayWalletInfo(std::string walletId) const {
    Wallet* wallet = findWallet(walletId);
    if (wallet) {
        wallet->displayInfo();
        wallet->displayTransactions();
    }
}

void WalletSystem::displayAllUsers() const {
    std::cout << "\nAll Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void WalletSystem::displayAllWallets() const {
    std::cout << "\nAll Wallets:" << std::endl;
    for (const auto& wallet : wallets) {
        wallet->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

User* WalletSystem::findUser(const std::string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Wallet* WalletSystem::findWallet(const std::string& walletId) const {
    for (auto wallet : wallets) {
        if (wallet->getWalletId() == walletId) return wallet;
    }
    return nullptr;
}

std::string WalletSystem::generateTransactionId() {
    return "T" + std::to_string(transactionIdCounter++);
}

std::string WalletSystem::getCurrentTimestamp() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
} 