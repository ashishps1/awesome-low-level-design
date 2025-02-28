#include "CartItem.hpp"
#include <iostream>
#include <iomanip>

CartItem::CartItem(Product* product, int quantity)
    : product(product), quantity(quantity) {}

Product* CartItem::getProduct() const { return product; }
int CartItem::getQuantity() const { return quantity; }

double CartItem::getSubtotal() const {
    return product->getPrice() * quantity;
}

void CartItem::setQuantity(int quantity) {
    if (quantity > 0) {
        this->quantity = quantity;
    }
}

void CartItem::displayInfo() const {
    std::cout << product->getName() << " x " << quantity 
              << " = $" << std::fixed << std::setprecision(2) 
              << getSubtotal() << std::endl;
} 