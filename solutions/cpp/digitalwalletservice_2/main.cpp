// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Transaction;
class User;
class Wallet;
class WalletSystem;

// ===== Transaction.hpp =====
enum class TransactionType {
    ADD_MONEY,
    WITHDRAW,
    TRANSFER
};

class Transaction {
private:
    string transactionId;
    string walletId;
    TransactionType type;
    double amount;
    string timestamp;
    string description;
    bool status;

public:
    Transaction(string transactionId, string walletId, 
               TransactionType type, double amount, string timestamp,
               string description);
    
    string getTransactionId() const;
    string getWalletId() const;
    TransactionType getType() const;
    double getAmount() const;
    string getTimestamp() const;
    string getDescription() const;
    bool getStatus() const;
    
    void setStatus(bool status);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string name;
    string email;
    string phoneNumber;

public:
    User(string userId, string name, string email, string phoneNumber);
    
    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPhoneNumber() const;
    void displayInfo() const;
};

// ===== Wallet.hpp =====
class Wallet {
private:
    string walletId;
    string userId;
    double balance;
    vector<Transaction*> transactions;

public:
    Wallet(string walletId, string userId);
    ~Wallet();
    
    string getWalletId() const;
    string getUserId() const;
    double getBalance() const;
    
    bool addMoney(double amount, string source);
    bool withdrawMoney(double amount, string destination);
    void addTransaction(Transaction* transaction);
    void displayInfo() const;
    void displayTransactions() const;
};

// ===== WalletSystem.hpp =====
class WalletSystem {
private:
    vector<User*> users;
    vector<Wallet*> wallets;
    int transactionIdCounter;

public:
    WalletSystem();
    ~WalletSystem();
    
    void addUser(User* user);
    Wallet* createWallet(string userId);
    
    bool addMoney(string walletId, double amount, string source);
    bool withdrawMoney(string walletId, double amount, string destination);
    bool transferMoney(string fromWalletId, string toWalletId, double amount);
    
    void displayUserInfo(string userId) const;
    void displayWalletInfo(string walletId) const;
    void displayAllUsers() const;
    void displayAllWallets() const;
    
private:
    User* findUser(const string& userId) const;
    Wallet* findWallet(const string& walletId) const;
    string generateTransactionId();
    string getCurrentTimestamp() const;
};

// ===== Transaction.cpp =====
Transaction::Transaction(string transactionId, string walletId, 
                       TransactionType type, double amount, string timestamp,
                       string description)
    : transactionId(transactionId), walletId(walletId), type(type), 
      amount(amount), timestamp(timestamp), description(description), status(false) {}

string Transaction::getTransactionId() const { return transactionId; }
string Transaction::getWalletId() const { return walletId; }
TransactionType Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
string Transaction::getTimestamp() const { return timestamp; }
string Transaction::getDescription() const { return description; }
bool Transaction::getStatus() const { return status; }

void Transaction::setStatus(bool status) {
    this->status = status;
}

void Transaction::displayInfo() const {
    cout << "Transaction ID: " << transactionId << endl;
    cout << "Type: ";
    switch (type) {
        case TransactionType::ADD_MONEY: cout << "Add Money"; break;
        case TransactionType::WITHDRAW: cout << "Withdraw"; break;
        case TransactionType::TRANSFER: cout << "Transfer"; break;
    }
    cout << endl;
    cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
    cout << "Time: " << timestamp << endl;
    cout << "Description: " << description << endl;
    cout << "Status: " << (status ? "Success" : "Pending") << endl;
} 

// ===== User.cpp =====
User::User(string userId, string name, string email, string phoneNumber)
    : userId(userId), name(name), email(email), phoneNumber(phoneNumber) {}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhoneNumber() const { return phoneNumber; }

void User::displayInfo() const {
    cout << "User: " << name << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phoneNumber << endl;
} 

// ===== Wallet.cpp =====
Wallet::Wallet(string walletId, string userId)
    : walletId(walletId), userId(userId), balance(0.0) {}

Wallet::~Wallet() {
    for (auto transaction : transactions) {
        delete transaction;
    }
}

string Wallet::getWalletId() const { return walletId; }
string Wallet::getUserId() const { return userId; }
double Wallet::getBalance() const { return balance; }

bool Wallet::addMoney(double amount, string source) {
    if (amount <= 0) return false;
    
    balance += amount;
    return true;
}

bool Wallet::withdrawMoney(double amount, string destination) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    return true;
}

void Wallet::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}

void Wallet::displayInfo() const {
    cout << "Wallet ID: " << walletId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
}

void Wallet::displayTransactions() const {
    cout << "\nTransaction History:" << endl;
    for (const auto& transaction : transactions) {
        transaction->displayInfo();
        cout << "------------------------" << endl;
    }
} 

// ===== WalletSystem.cpp =====
WalletSystem::WalletSystem() : transactionIdCounter(1) {}

WalletSystem::~WalletSystem() {
    for (auto user : users) delete user;
    for (auto wallet : wallets) delete wallet;
}

void WalletSystem::addUser(User* user) {
    users.push_back(user);
}

Wallet* WalletSystem::createWallet(string userId) {
    if (!findUser(userId)) return nullptr;
    
    string walletId = "W" + userId;
    Wallet* wallet = new Wallet(walletId, userId);
    wallets.push_back(wallet);
    return wallet;
}

bool WalletSystem::addMoney(string walletId, double amount, string source) {
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

bool WalletSystem::withdrawMoney(string walletId, double amount, string destination) {
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

bool WalletSystem::transferMoney(string fromWalletId, string toWalletId, double amount) {
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

void WalletSystem::displayUserInfo(string userId) const {
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

void WalletSystem::displayWalletInfo(string walletId) const {
    Wallet* wallet = findWallet(walletId);
    if (wallet) {
        wallet->displayInfo();
        wallet->displayTransactions();
    }
}

void WalletSystem::displayAllUsers() const {
    cout << "\nAll Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void WalletSystem::displayAllWallets() const {
    cout << "\nAll Wallets:" << endl;
    for (const auto& wallet : wallets) {
        wallet->displayInfo();
        cout << "------------------------" << endl;
    }
}

User* WalletSystem::findUser(const string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Wallet* WalletSystem::findWallet(const string& walletId) const {
    for (auto wallet : wallets) {
        if (wallet->getWalletId() == walletId) return wallet;
    }
    return nullptr;
}

string WalletSystem::generateTransactionId() {
    return "T" + to_string(transactionIdCounter++);
}

string WalletSystem::getCurrentTimestamp() const {
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
} 

// ===== WalletDemo.cpp =====
int main() {
    WalletSystem system;
    
    // Create users
    User* user1 = new User("U001", "John Doe", "john@example.com", "+1-555-0123");
    User* user2 = new User("U002", "Jane Smith", "jane@example.com", "+1-555-0124");
    
    system.addUser(user1);
    system.addUser(user2);
    
    // Create wallets
    Wallet* wallet1 = system.createWallet("U001");
    Wallet* wallet2 = system.createWallet("U002");
    
    // Add money to wallets
    if (system.addMoney("WU001", 1000.0, "Bank Transfer")) {
        cout << "Added $1000 to John's wallet" << endl;
    }
    
    if (system.addMoney("WU002", 500.0, "Credit Card")) {
        cout << "Added $500 to Jane's wallet" << endl;
    }
    
    // Transfer money
    if (system.transferMoney("WU001", "WU002", 300.0)) {
        cout << "Transferred $300 from John to Jane" << endl;
    }
    
    // Withdraw money
    if (system.withdrawMoney("WU002", 200.0, "Bank Account")) {
        cout << "Jane withdrew $200" << endl;
    }
    
    // Display information
    system.displayAllUsers();
    system.displayAllWallets();
    
    // Display detailed user information
    cout << "\nDetailed User Information:" << endl;
    system.displayUserInfo("U001");
    
    return 0;
} 

