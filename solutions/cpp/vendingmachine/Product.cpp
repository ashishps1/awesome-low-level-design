#include "Product.hpp"
#include <iostream>
#include <iomanip>

Product::Product(std::string productId, std::string name, double price, int quantity)
    : productId(productId), name(name), price(price), quantity(quantity), available(true) {}

std::string Product::getProductId() const { return productId; }
std::string Product::getName() const { return name; }
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
    std::cout << "Product: " << name << " (ID: " << productId << ")" << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Status: " << (isAvailable() ? "Available" : "Not Available") << std::endl;
} 