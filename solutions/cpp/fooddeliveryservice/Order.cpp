#include "Order.hpp"
#include <iostream>
#include <iomanip>

Order::Order(std::string orderId, User* user, Restaurant* restaurant)
    : orderId(orderId), user(user), restaurant(restaurant), 
      status(OrderStatus::PLACED), totalAmount(0.0) {
    // Get current timestamp
    auto now = std::time(nullptr);
    timestamp = std::ctime(&now);
}

std::string Order::getOrderId() const { return orderId; }
User* Order::getUser() const { return user; }
Restaurant* Order::getRestaurant() const { return restaurant; }
OrderStatus Order::getStatus() const { return status; }
double Order::getTotalAmount() const { return totalAmount; }
std::string Order::getTimestamp() const { return timestamp; }

void Order::addItem(MenuItem* item, int quantity) {
    if (item && quantity > 0) {
        items[item] = quantity;
        calculateTotal();
    }
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& pair : items) {
        totalAmount += pair.first->getPrice() * pair.second;
    }
}

void Order::displayInfo() const {
    std::cout << "\nOrder Details:" << std::endl;
    std::cout << "Order ID: " << orderId << std::endl;
    std::cout << "Customer: " << user->getName() << std::endl;
    std::cout << "Restaurant: " << restaurant->getName() << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case OrderStatus::PLACED: std::cout << "Placed"; break;
        case OrderStatus::PREPARING: std::cout << "Preparing"; break;
        case OrderStatus::OUT_FOR_DELIVERY: std::cout << "Out for Delivery"; break;
        case OrderStatus::DELIVERED: std::cout << "Delivered"; break;
        case OrderStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
    
    std::cout << "\nOrdered Items:" << std::endl;
    for (const auto& pair : items) {
        std::cout << pair.first->getName() << " x " << pair.second 
                  << " = $" << std::fixed << std::setprecision(2)
                  << pair.first->getPrice() * pair.second << std::endl;
    }
    
    std::cout << "\nTotal Amount: $" << std::fixed << std::setprecision(2) 
              << totalAmount << std::endl;
    std::cout << "Order Time: " << timestamp;
} 