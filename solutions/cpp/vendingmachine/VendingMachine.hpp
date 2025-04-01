#ifndef VENDING_MACHINE_HPP
#define VENDING_MACHINE_HPP

#include <vector>
#include <string>
#include "Product.hpp"
#include "Transaction.hpp"

class VendingMachine {
private:
    std::string machineId;
    std::vector<Product*> products;
    std::vector<Transaction*> transactions;
    double cashBalance;
    bool operational;
    int productIdCounter;
    int transactionIdCounter;

public:
    VendingMachine(std::string machineId);
    ~VendingMachine();
    
    std::string getMachineId() const;
    double getCashBalance() const;
    bool isOperational() const;
    
    Product* addProduct(const std::string& name, double price, int quantity = 0);
    void removeProduct(const std::string& productId);
    bool restockProduct(const std::string& productId, int quantity);
    bool updatePrice(const std::string& productId, double price);
    Transaction* purchaseProduct(const std::string& productId, int quantity, double payment);
    void addCash(double amount);
    bool withdrawCash(double amount);
    void setOperational(bool status);
    
    void displayInventory() const;
    void displayTransactions() const;
    void displayMachineInfo() const;

private:
    Product* findProduct(const std::string& productId) const;
    std::string generateProductId();
    std::string generateTransactionId();
};

#endif 