#include "Cart.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

Cart::Cart(User* user) : user(user), total(0.0) {}

Cart::~Cart() {
    clear();
}

User* Cart::getUser() const { return user; }
const std::vector<CartItem*>& Cart::getItems() const { return items; }
double Cart::getTotal() const { return total; }

bool Cart::addItem(Product* product, int quantity) {
    if (!product->isAvailable() || quantity <= 0 || 
        quantity > product->getStockQuantity()) {
        return false;
    }

    // Check if product already exists in cart
    for (auto item : items) {
        if (item->getProduct() == product) {
            return updateItemQuantity(product, item->getQuantity() + quantity);
        }
    }

    items.push_back(new CartItem(product, quantity));
    calculateTotal();
    return true;
}

bool Cart::updateItemQuantity(Product* product, int quantity) {
    if (quantity <= 0 || quantity > product->getStockQuantity()) {
        return false;
    }

    for (auto item : items) {
        if (item->getProduct() == product) {
            item->setQuantity(quantity);
            calculateTotal();
            return true;
        }
    }
    return false;
}

bool Cart::removeItem(Product* product) {
    auto it = std::find_if(items.begin(), items.end(),
        [product](CartItem* item) { return item->getProduct() == product; });
    
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        calculateTotal();
        return true;
    }
    return false;
}

void Cart::clear() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
    total = 0.0;
}

void Cart::calculateTotal() {
    total = 0.0;
    for (const auto& item : items) {
        total += item->getSubtotal();
    }
}

void Cart::displayInfo() const {
    std::cout << "\nShopping Cart for " << user->getUsername() << ":" << std::endl;
    std::cout << "Items:" << std::endl;
    for (const auto& item : items) {
        item->displayInfo();
    }
    std::cout << "------------------------" << std::endl;
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << total << std::endl;
} 