// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Product;
class Transaction;
class VendingMachine;

// ===== Product.hpp =====
class Product {
private:
    string productId;
    string name;
    double price;
    int quantity;
    bool available;

public:
    Product(string productId, string name, double price, int quantity = 0);
    
    string getProductId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
    bool isAvailable() const;
    
    void setPrice(double price);
    void setQuantity(int quantity);
    void setAvailable(bool status);
    void addQuantity(int amount);
    bool removeQuantity(int amount);
    void displayInfo() const;
};

// ===== Transaction.hpp =====
class Transaction {
private:
    string transactionId;
    string productId;
    int quantity;
    double amount;
    time_t timestamp;
    bool successful;

public:
    Transaction(string transactionId, string productId, int quantity, double amount);
    
    string getTransactionId() const;
    string getProductId() const;
    int getQuantity() const;
    double getAmount() const;
    time_t getTimestamp() const;
    bool isSuccessful() const;
    
    void setSuccessful(bool status);
    void displayInfo() const;
};

// ===== VendingMachine.hpp =====
class VendingMachine {
private:
    string machineId;
    vector<Product*> products;
    vector<Transaction*> transactions;
    double cashBalance;
    bool operational;
    int productIdCounter;
    int transactionIdCounter;

public:
    VendingMachine(string machineId);
    ~VendingMachine();
    
    string getMachineId() const;
    double getCashBalance() const;
    bool isOperational() const;
    
    Product* addProduct(const string& name, double price, int quantity = 0);
    void removeProduct(const string& productId);
    bool restockProduct(const string& productId, int quantity);
    bool updatePrice(const string& productId, double price);
    Transaction* purchaseProduct(const string& productId, int quantity, double payment);
    void addCash(double amount);
    bool withdrawCash(double amount);
    void setOperational(bool status);
    
    void displayInventory() const;
    void displayTransactions() const;
    void displayMachineInfo() const;

private:
    Product* findProduct(const string& productId) const;
    string generateProductId();
    string generateTransactionId();
};

// ===== Product.cpp =====
Product::Product(string productId, string name, double price, int quantity)
    : productId(productId), name(name), price(price), quantity(quantity), available(true) {}

string Product::getProductId() const { return productId; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
bool Product::isAvailable() const { return available && quantity > 0; }

void Product::setPrice(double price) {
    this->price = price;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Product::setAvailable(bool status) {
    available = status;
}

void Product::addQuantity(int amount) {
    quantity += amount;
}

bool Product::removeQuantity(int amount) {
    if (amount <= quantity) {
        quantity -= amount;
        return true;
    }
    return false;
}

void Product::displayInfo() const {
    cout << "Product: " << name << " (ID: " << productId << ")" << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Status: " << (isAvailable() ? "Available" : "Not Available") << endl;
} 

// ===== Transaction.cpp =====
Transaction::Transaction(string transactionId, string productId, int quantity, double amount)
    : transactionId(transactionId), productId(productId), quantity(quantity), amount(amount),
      successful(false) {
    timestamp = time(nullptr);
}

string Transaction::getTransactionId() const { return transactionId; }
string Transaction::getProductId() const { return productId; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getAmount() const { return amount; }
time_t Transaction::getTimestamp() const { return timestamp; }
bool Transaction::isSuccessful() const { return successful; }

void Transaction::setSuccessful(bool status) {
    successful = status;
}

void Transaction::displayInfo() const {
    cout << "Transaction " << transactionId << ":" << endl;
    cout << "Product ID: " << productId << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
    cout << "Status: " << (successful ? "Successful" : "Failed") << endl;
    cout << "Time: " << ctime(&timestamp);
} 

// ===== VendingMachine.cpp =====
VendingMachine::VendingMachine(string machineId)
    : machineId(machineId), cashBalance(0.0), operational(true),
      productIdCounter(1), transactionIdCounter(1) {}

VendingMachine::~VendingMachine() {
    for (auto product : products) delete product;
    for (auto transaction : transactions) delete transaction;
}

string VendingMachine::getMachineId() const { return machineId; }
double VendingMachine::getCashBalance() const { return cashBalance; }
bool VendingMachine::isOperational() const { return operational; }

Product* VendingMachine::addProduct(const string& name, double price, int quantity) {
    string productId = generateProductId();
    Product* product = new Product(productId, name, price, quantity);
    products.push_back(product);
    return product;
}

void VendingMachine::removeProduct(const string& productId) {
    auto it = find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    
    if (it != products.end()) {
        delete *it;
        products.erase(it);
    }
}

bool VendingMachine::restockProduct(const string& productId, int quantity) {
    Product* product = findProduct(productId);
    if (!product) return false;
    
    product->addQuantity(quantity);
    return true;
}

bool VendingMachine::updatePrice(const string& productId, double price) {
    Product* product = findProduct(productId);
    if (!product) return false;
    
    product->setPrice(price);
    return true;
}

Transaction* VendingMachine::purchaseProduct(const string& productId, int quantity, double payment) {
    if (!operational) return nullptr;
    
    Product* product = findProduct(productId);
    if (!product || !product->isAvailable() || product->getQuantity()<quantity) return nullptr;
    
    double totalCost = product->getPrice() * quantity;
    if (payment < totalCost) return nullptr;
    
    string transactionId = generateTransactionId();
    Transaction* transaction = new Transaction(transactionId, productId, quantity, totalCost);
    
    if (product->removeQuantity(quantity)) {
        cashBalance += totalCost;
        transaction->setSuccessful(true);
        transactions.push_back(transaction);
        return transaction;
    }
    
    delete transaction;
    return nullptr;
}

void VendingMachine::addCash(double amount) {
    cashBalance += amount;
}

bool VendingMachine::withdrawCash(double amount) {
    if (amount <= cashBalance) {
        cashBalance -= amount;
        return true;
    }
    return false;
}

void VendingMachine::setOperational(bool status) {
    operational = status;
}

void VendingMachine::displayInventory() const {
    cout << "\nCurrent Inventory:" << endl;
    for (const auto& product : products) {
        product->displayInfo();
        cout << "------------------------" << endl;
    }
}

void VendingMachine::displayTransactions() const {
    cout << "\nTransaction History:" << endl;
    for (const auto& transaction : transactions) {
        transaction->displayInfo();
        cout << "------------------------" << endl;
    }
}

void VendingMachine::displayMachineInfo() const {
    cout << "\nVending Machine Info:" << endl;
    cout << "ID: " << machineId << endl;
    cout << "Status: " << (operational ? "Operational" : "Out of Service") << endl;
    cout << "Cash Balance: $" << fixed << setprecision(2) << cashBalance << endl;
    cout << "Products Available: " << products.size() << endl;
    cout << "Total Transactions: " << transactions.size() << endl;
}

Product* VendingMachine::findProduct(const string& productId) const {
    auto it = find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    return it != products.end() ? *it : nullptr;
}

string VendingMachine::generateProductId() {
    return "P" + to_string(productIdCounter++);
}

string VendingMachine::generateTransactionId() {
    return "T" + to_string(transactionIdCounter++);
} 

// ===== VendingMachineDemo.cpp =====
int main() {
    VendingMachine machine("VM001");
    
    // Add products
    Product* cola = machine.addProduct("Cola", 2.50, 10);
    Product* chips = machine.addProduct("Chips", 1.50, 15);
    Product* candy = machine.addProduct("Candy", 1.00, 20);
    
    // Display initial inventory
    cout << "Initial machine status:" << endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    // Make some purchases
    cout << "\nMaking purchases..." << endl;
    Transaction* t1 = machine.purchaseProduct(cola->getProductId(), 2, 5.00);
    Transaction* t2 = machine.purchaseProduct(chips->getProductId(), 3, 5.00);
    
    // Display transactions
    machine.displayTransactions();
    
    // Restock a product
    cout << "\nRestocking Cola..." << endl;
    machine.restockProduct(cola->getProductId(), 5);
    
    // Update price
    cout << "\nUpdating Candy price..." << endl;
    machine.updatePrice(candy->getProductId(), 1.25);
    
    // Display final status
    cout << "\nFinal machine status:" << endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    return 0;
} 

