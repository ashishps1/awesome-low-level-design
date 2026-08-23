// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Stock;
class Portfolio;
class User;
class Transaction;
class BrokerageSystem;

// ===== Stock.hpp =====
class Stock {
private:
    string symbol;
    string companyName;
    double currentPrice;
    int availableShares;
    bool active;

public:
    Stock(string symbol, string companyName, double currentPrice, int availableShares);
    
    string getSymbol() const;
    string getCompanyName() const;
    double getCurrentPrice() const;
    int getAvailableShares() const;
    bool isActive() const;
    
    void setCurrentPrice(double price);
    void updateShares(int quantity);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Portfolio.hpp =====
class Portfolio {
private:
    string userId;
    map<string, int> holdings;  // symbol -> quantity
    double totalValue;

public:
    Portfolio(string userId);
    
    string getUserId() const;
    const map<string, int>& getHoldings() const;
    double getTotalValue() const;
    int getShareQuantity(const string& symbol) const;
    
    void addShares(const string& symbol, int quantity);
    bool removeShares(const string& symbol, int quantity);
    void updateTotalValue(const map<string, Stock*>& stocks);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    double balance;
    Portfolio* portfolio;
    bool active;

public:
    User(string userId, string username, string email);
    ~User();
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    double getBalance() const;
    Portfolio* getPortfolio() const;
    bool isActive() const;
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Transaction.hpp =====
enum class TransactionType {
    BUY,
    SELL
};

class Transaction {
private:
    string transactionId;
    User* user;
    Stock* stock;
    TransactionType type;
    int quantity;
    double pricePerShare;
    double totalAmount;
    time_t timestamp;

public:
    Transaction(string transactionId, User* user, Stock* stock,
               TransactionType type, int quantity, double pricePerShare);
    
    string getTransactionId() const;
    User* getUser() const;
    Stock* getStock() const;
    TransactionType getType() const;
    int getQuantity() const;
    double getPricePerShare() const;
    double getTotalAmount() const;
    time_t getTimestamp() const;
    
    void displayInfo() const;
};

// ===== BrokerageSystem.hpp =====
class BrokerageSystem {
private:
    vector<User*> users;
    map<string, Stock*> stocks;  // symbol -> Stock*
    vector<Transaction*> transactions;
    int transactionIdCounter;

public:
    BrokerageSystem();
    ~BrokerageSystem();
    
    // User management
    User* registerUser(const string& username, const string& email);
    void removeUser(const string& userId);
    
    // Stock management
    Stock* addStock(const string& symbol, const string& companyName,
                   double price, int shares);
    void updateStockPrice(const string& symbol, double newPrice);
    
    // Trading operations
    bool deposit(const string& userId, double amount);
    bool withdraw(const string& userId, double amount);
    Transaction* buyStock(const string& userId, const string& symbol, int quantity);
    Transaction* sellStock(const string& userId, const string& symbol, int quantity);
    
    // Display functions
    void displayStocks() const;
    void displayUsers() const;
    void displayUserPortfolio(const string& userId) const;
    void displayTransactionHistory(const string& userId) const;
    
private:
    User* findUser(const string& userId) const;
    Stock* findStock(const string& symbol) const;
    void updatePortfolioValues();
    string generateTransactionId();
};

// ===== BrokerageSystem.cpp =====
BrokerageSystem::BrokerageSystem() : transactionIdCounter(1) {}

BrokerageSystem::~BrokerageSystem() {
    for (auto user : users) delete user;
    for (auto& pair : stocks) delete pair.second;
    for (auto transaction : transactions) delete transaction;
}

User* BrokerageSystem::registerUser(const string& username, const string& email) {
    string userId = "U" + to_string(users.size() + 1);
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void BrokerageSystem::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Stock* BrokerageSystem::addStock(const string& symbol, const string& companyName,
                                double price, int shares) {
    Stock* stock = new Stock(symbol, companyName, price, shares);
    stocks[symbol] = stock;
    return stock;
}

void BrokerageSystem::updateStockPrice(const string& symbol, double newPrice) {
    if (Stock* stock = findStock(symbol)) {
        stock->setCurrentPrice(newPrice);
        updatePortfolioValues();
    }
}

bool BrokerageSystem::deposit(const string& userId, double amount) {
    if (User* user = findUser(userId)) {
        return user->deposit(amount);
    }
    return false;
}

bool BrokerageSystem::withdraw(const string& userId, double amount) {
    if (User* user = findUser(userId)) {
        return user->withdraw(amount);
    }
    return false;
}

Transaction* BrokerageSystem::buyStock(const string& userId, const string& symbol, int quantity) {
    User* user = findUser(userId);
    Stock* stock = findStock(symbol);
    
    if (!user || !stock || !stock->isActive()) return nullptr;
    
    double totalCost = stock->getCurrentPrice() * quantity;
    if (user->getBalance() < totalCost || stock->getAvailableShares() < quantity) {
        return nullptr;
    }
    
    // Process transaction
    user->withdraw(totalCost);
    stock->updateShares(-quantity);
    user->getPortfolio()->addShares(symbol, quantity);
    
    // Create transaction record
    Transaction* transaction = new Transaction(generateTransactionId(), user, stock,
                                            TransactionType::BUY, quantity,
                                            stock->getCurrentPrice());
    transactions.push_back(transaction);
    
    updatePortfolioValues();
    return transaction;
}

Transaction* BrokerageSystem::sellStock(const string& userId, const string& symbol, int quantity) {
    User* user = findUser(userId);
    Stock* stock = findStock(symbol);
    
    if (!user || !stock || !stock->isActive()) return nullptr;
    
    Portfolio* portfolio = user->getPortfolio();
    if (portfolio->getShareQuantity(symbol) < quantity) {
        return nullptr;
    }
    
    // Process transaction
    double totalAmount = stock->getCurrentPrice() * quantity;
    user->deposit(totalAmount);
    stock->updateShares(quantity);
    portfolio->removeShares(symbol, quantity);
    
    // Create transaction record
    Transaction* transaction = new Transaction(generateTransactionId(), user, stock,
                                            TransactionType::SELL, quantity,
                                            stock->getCurrentPrice());
    transactions.push_back(transaction);
    
    updatePortfolioValues();
    return transaction;
}

void BrokerageSystem::displayStocks() const {
    cout << "\nAvailable Stocks:" << endl;
    for (const auto& pair : stocks) {
        pair.second->displayInfo();
        cout << "------------------------" << endl;
    }
}

void BrokerageSystem::displayUsers() const {
    cout << "\nRegistered Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void BrokerageSystem::displayUserPortfolio(const string& userId) const {
    if (User* user = findUser(userId)) {
        user->getPortfolio()->displayInfo();
    }
}

void BrokerageSystem::displayTransactionHistory(const string& userId) const {
    cout << "\nTransaction History:" << endl;
    for (const auto& transaction : transactions) {
        if (transaction->getUser()->getUserId() == userId) {
            transaction->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

User* BrokerageSystem::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Stock* BrokerageSystem::findStock(const string& symbol) const {
    auto it = stocks.find(symbol);
    return it != stocks.end() ? it->second : nullptr;
}

void BrokerageSystem::updatePortfolioValues() {
    for (auto user : users) {
        user->getPortfolio()->updateTotalValue(stocks);
    }
}

string BrokerageSystem::generateTransactionId() {
    return "T" + to_string(transactionIdCounter++);
} 

// ===== Portfolio.cpp =====
Portfolio::Portfolio(string userId) : userId(userId), totalValue(0.0) {}

string Portfolio::getUserId() const { return userId; }
const map<string, int>& Portfolio::getHoldings() const { return holdings; }
double Portfolio::getTotalValue() const { return totalValue; }

int Portfolio::getShareQuantity(const string& symbol) const {
    auto it = holdings.find(symbol);
    return it != holdings.end() ? it->second : 0;
}

void Portfolio::addShares(const string& symbol, int quantity) {
    if (quantity > 0) {
        holdings[symbol] += quantity;
    }
}

bool Portfolio::removeShares(const string& symbol, int quantity) {
    auto it = holdings.find(symbol);
    if (it != holdings.end() && it->second >= quantity) {
        it->second -= quantity;
        if (it->second == 0) {
            holdings.erase(it);
        }
        return true;
    }
    return false;
}

void Portfolio::updateTotalValue(const map<string, Stock*>& stocks) {
    totalValue = 0.0;
    for (const auto& holding : holdings) {
        auto stockIt = stocks.find(holding.first);
        if (stockIt != stocks.end()) {
            totalValue += stockIt->second->getCurrentPrice() * holding.second;
        }
    }
}

void Portfolio::displayInfo() const {
    cout << "\nPortfolio Holdings:" << endl;
    if (holdings.empty()) {
        cout << "No holdings" << endl;
    } else {
        for (const auto& holding : holdings) {
            cout << holding.first << ": " << holding.second << " shares" << endl;
        }
    }
    cout << "Total Value: $" << fixed << setprecision(2) << totalValue << endl;
} 

// ===== Stock.cpp =====
Stock::Stock(string symbol, string companyName, double currentPrice, int availableShares)
    : symbol(symbol), companyName(companyName), currentPrice(currentPrice), 
      availableShares(availableShares), active(true) {}

string Stock::getSymbol() const { return symbol; }
string Stock::getCompanyName() const { return companyName; }
double Stock::getCurrentPrice() const { return currentPrice; }
int Stock::getAvailableShares() const { return availableShares; }
bool Stock::isActive() const { return active; }

void Stock::setCurrentPrice(double price) {
    if (price > 0) {
        currentPrice = price;
    }
}

void Stock::updateShares(int quantity) {
    if (availableShares + quantity >= 0) {
        availableShares += quantity;
        active = (availableShares > 0);
    }
}

void Stock::setActive(bool status) {
    active = status;
}

void Stock::displayInfo() const {
    cout << "Stock: " << companyName << " (" << symbol << ")" << endl;
    cout << "Current Price: $" << fixed << setprecision(2) << currentPrice << endl;
    cout << "Available Shares: " << availableShares << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
} 

// ===== Transaction.cpp =====
Transaction::Transaction(string transactionId, User* user, Stock* stock,
                       TransactionType type, int quantity, double pricePerShare)
    : transactionId(transactionId), user(user), stock(stock), type(type),
      quantity(quantity), pricePerShare(pricePerShare) {
    totalAmount = quantity * pricePerShare;
    timestamp = time(nullptr);
}

string Transaction::getTransactionId() const { return transactionId; }
User* Transaction::getUser() const { return user; }
Stock* Transaction::getStock() const { return stock; }
TransactionType Transaction::getType() const { return type; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getPricePerShare() const { return pricePerShare; }
double Transaction::getTotalAmount() const { return totalAmount; }
time_t Transaction::getTimestamp() const { return timestamp; }

void Transaction::displayInfo() const {
    cout << "\nTransaction Details:" << endl;
    cout << "ID: " << transactionId << endl;
    cout << "Type: " << (type == TransactionType::BUY ? "Buy" : "Sell") << endl;
    cout << "Stock: " << stock->getSymbol() << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price per Share: $" << fixed << setprecision(2) << pricePerShare << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "Time: " << ctime(&timestamp);
} 

// ===== User.cpp =====
User::User(string userId, string username, string email)
    : userId(userId), username(username), email(email), balance(0.0), active(true) {
    portfolio = new Portfolio(userId);
}

User::~User() {
    delete portfolio;
}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
double User::getBalance() const { return balance; }
Portfolio* User::getPortfolio() const { return portfolio; }
bool User::isActive() const { return active; }

bool User::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool User::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    portfolio->displayInfo();
} 

// ===== BrokerageDemo.cpp =====
int main() {
    BrokerageSystem brokerage;
    
    // Add stocks
    Stock* apple = brokerage.addStock("AAPL", "Apple Inc.", 150.0, 1000);
    Stock* google = brokerage.addStock("GOOGL", "Alphabet Inc.", 2800.0, 500);
    Stock* amazon = brokerage.addStock("AMZN", "Amazon.com Inc.", 3300.0, 300);
    
    cout << "Initial Stocks:" << endl;
    brokerage.displayStocks();
    
    // Register users
    User* user1 = brokerage.registerUser("john_trader", "john@email.com");
    User* user2 = brokerage.registerUser("jane_investor", "jane@email.com");
    
    // Deposit funds
    brokerage.deposit(user1->getUserId(), 10000.0);
    brokerage.deposit(user2->getUserId(), 15000.0);
    
    cout << "\nUsers after deposit:" << endl;
    brokerage.displayUsers();
    
    // Perform transactions
    Transaction* trans1 = brokerage.buyStock(user1->getUserId(), "AAPL", 10);
    if (trans1) {
        cout << "\nBuy Transaction:" << endl;
        trans1->displayInfo();
    }
    
    // Update stock price
    brokerage.updateStockPrice("AAPL", 155.0);
    
    Transaction* trans2 = brokerage.sellStock(user1->getUserId(), "AAPL", 5);
    if (trans2) {
        cout << "\nSell Transaction:" << endl;
        trans2->displayInfo();
    }
    
    // Display final state
    cout << "\nFinal Portfolio for John:" << endl;
    brokerage.displayUserPortfolio(user1->getUserId());
    
    cout << "\nTransaction History for John:" << endl;
    brokerage.displayTransactionHistory(user1->getUserId());
    
    return 0;
} 

