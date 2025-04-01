#include "VendingMachine.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

VendingMachine::VendingMachine(std::string machineId)
    : machineId(machineId), cashBalance(0.0), operational(true),
      productIdCounter(1), transactionIdCounter(1) {}

VendingMachine::~VendingMachine() {
    for (auto product : products) delete product;
    for (auto transaction : transactions) delete transaction;
}

std::string VendingMachine::getMachineId() const { return machineId; }
double VendingMachine::getCashBalance() const { return cashBalance; }
bool VendingMachine::isOperational() const { return operational; }

Product* VendingMachine::addProduct(const std::string& name, double price, int quantity) {
    std::string productId = generateProductId();
    Product* product = new Product(productId, name, price, quantity);
    products.push_back(product);
    return product;
}

void VendingMachine::removeProduct(const std::string& productId) {
    auto it = std::find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    
    if (it != products.end()) {
        delete *it;
        products.erase(it);
    }
}

bool VendingMachine::restockProduct(const std::string& productId, int quantity) {
    Product* product = findProduct(productId);
    if (!product) return false;
    
    product->addQuantity(quantity);
    return true;
}

bool VendingMachine::updatePrice(const std::string& productId, double price) {
    Product* product = findProduct(productId);
    if (!product) return false;
    
    product->setPrice(price);
    return true;
}

Transaction* VendingMachine::purchaseProduct(const std::string& productId, int quantity, double payment) {
    if (!operational) return nullptr;
    
    Product* product = findProduct(productId);
    if (!product || !product->isAvailable() || product->getQuantity()<quantity) return nullptr;
    
    double totalCost = product->getPrice() * quantity;
    if (payment < totalCost) return nullptr;
    
    std::string transactionId = generateTransactionId();
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
    std::cout << "\nCurrent Inventory:" << std::endl;
    for (const auto& product : products) {
        product->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void VendingMachine::displayTransactions() const {
    std::cout << "\nTransaction History:" << std::endl;
    for (const auto& transaction : transactions) {
        transaction->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void VendingMachine::displayMachineInfo() const {
    std::cout << "\nVending Machine Info:" << std::endl;
    std::cout << "ID: " << machineId << std::endl;
    std::cout << "Status: " << (operational ? "Operational" : "Out of Service") << std::endl;
    std::cout << "Cash Balance: $" << std::fixed << std::setprecision(2) << cashBalance << std::endl;
    std::cout << "Products Available: " << products.size() << std::endl;
    std::cout << "Total Transactions: " << transactions.size() << std::endl;
}

Product* VendingMachine::findProduct(const std::string& productId) const {
    auto it = std::find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    return it != products.end() ? *it : nullptr;
}

std::string VendingMachine::generateProductId() {
    return "P" + std::to_string(productIdCounter++);
}

std::string VendingMachine::generateTransactionId() {
    return "T" + std::to_string(transactionIdCounter++);
} 