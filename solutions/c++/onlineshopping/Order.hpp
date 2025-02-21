#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>
#include <ctime>
#include "CartItem.hpp"

enum class OrderStatus {
    PENDING,
    CONFIRMED,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    std::string orderId;
    User* user;
    std::vector<CartItem*> items;
    double totalAmount;
    std::time_t orderDate;
    OrderStatus status;

public:
    Order(std::string orderId, User* user, const std::vector<CartItem*>& items);
    ~Order();
    
    std::string getOrderId() const;
    User* getUser() const;
    const std::vector<CartItem*>& getItems() const;
    double getTotalAmount() const;
    std::time_t getOrderDate() const;
    OrderStatus getStatus() const;
    
    void setStatus(OrderStatus status);
    void displayInfo() const;
};

#endif 