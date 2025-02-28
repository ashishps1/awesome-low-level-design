#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>
#include <map>
#include "User.hpp"
#include "Restaurant.hpp"
#include "MenuItem.hpp"

enum class OrderStatus {
    PLACED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    std::string orderId;
    User* user;
    Restaurant* restaurant;
    std::map<MenuItem*, int> items;  // item and quantity
    OrderStatus status;
    double totalAmount;
    std::string timestamp;

public:
    Order(std::string orderId, User* user, Restaurant* restaurant);
    
    std::string getOrderId() const;
    User* getUser() const;
    Restaurant* getRestaurant() const;
    OrderStatus getStatus() const;
    double getTotalAmount() const;
    std::string getTimestamp() const;
    
    void addItem(MenuItem* item, int quantity);
    void setStatus(OrderStatus status);
    void calculateTotal();
    void displayInfo() const;
};

#endif 