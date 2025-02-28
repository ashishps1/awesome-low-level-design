#include "Order.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

Order::Order(std::string orderId, Table* table)
    : orderId(orderId), table(table), totalAmount(0.0), status(OrderStatus::PENDING) {
    orderTime = std::time(nullptr);
}

Order::~Order() {
    for (auto item : items) {
        delete item;
    }
}

std::string Order::getOrderId() const { return orderId; }
Table* Order::getTable() const { return table; }
const std::vector<OrderItem*>& Order::getItems() const { return items; }
double Order::getTotalAmount() const { return totalAmount; }
std::time_t Order::getOrderTime() const { return orderTime; }
OrderStatus Order::getStatus() const { return status; }

void Order::addItem(MenuItem* menuItem, int quantity) {
    if (!menuItem || !menuItem->isAvailable()) return;
    
    // Check if item already exists
    auto it = std::find_if(items.begin(), items.end(),
        [menuItem](OrderItem* item) { return item->getMenuItem() == menuItem; });
    
    if (it != items.end()) {
        (*it)->updateQuantity((*it)->getQuantity() + quantity);
    } else {
        items.push_back(new OrderItem(menuItem, quantity));
    }
    
    calculateTotal();
}

void Order::removeItem(const std::string& itemId) {
    auto it = std::find_if(items.begin(), items.end(),
        [itemId](OrderItem* item) { return item->getMenuItem()->getItemId() == itemId; });
    
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        calculateTotal();
    }
}

void Order::updateItemQuantity(const std::string& itemId, int quantity) {
    auto it = std::find_if(items.begin(), items.end(),
        [itemId](OrderItem* item) { return item->getMenuItem()->getItemId() == itemId; });
    
    if (it != items.end()) {
        if (quantity <= 0) {
            removeItem(itemId);
        } else {
            (*it)->updateQuantity(quantity);
            calculateTotal();
        }
    }
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item->getSubtotal();
    }
}

void Order::displayInfo() const {
    std::cout << "\nOrder Details:" << std::endl;
    std::cout << "Order ID: " << orderId << std::endl;
    std::cout << "Table: " << table->getTableNumber() << std::endl;
    std::cout << "Time: " << std::ctime(&orderTime);
    std::cout << "Status: ";
    switch (status) {
        case OrderStatus::PENDING: std::cout << "Pending"; break;
        case OrderStatus::PREPARING: std::cout << "Preparing"; break;
        case OrderStatus::READY: std::cout << "Ready"; break;
        case OrderStatus::SERVED: std::cout << "Served"; break;
        case OrderStatus::PAID: std::cout << "Paid"; break;
    }
    std::cout << std::endl;
    
    std::cout << "\nItems:" << std::endl;
    for (const auto& item : items) {
        item->displayInfo();
    }
    std::cout << "------------------------" << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
} 