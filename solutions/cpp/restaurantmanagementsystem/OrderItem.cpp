#include "OrderItem.hpp"
#include <iostream>
#include <iomanip>

OrderItem::OrderItem(MenuItem* menuItem, int quantity)
    : menuItem(menuItem), quantity(quantity) {
    subtotal = menuItem->getPrice() * quantity;
}

MenuItem* OrderItem::getMenuItem() const { return menuItem; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getSubtotal() const { return subtotal; }

void OrderItem::updateQuantity(int quantity) {
    if (quantity > 0) {
        this->quantity = quantity;
        subtotal = menuItem->getPrice() * quantity;
    }
}

void OrderItem::displayInfo() const {
    std::cout << menuItem->getName() << " x " << quantity 
              << " = $" << std::fixed << std::setprecision(2) << subtotal << std::endl;
} 