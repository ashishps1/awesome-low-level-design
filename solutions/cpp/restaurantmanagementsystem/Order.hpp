#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>
#include <ctime>
#include "Table.hpp"
#include "OrderItem.hpp"

enum class OrderStatus {
    PENDING,
    PREPARING,
    READY,
    SERVED,
    PAID
};

class Order {
private:
    std::string orderId;
    Table* table;
    std::vector<OrderItem*> items;
    double totalAmount;
    std::time_t orderTime;
    OrderStatus status;

public:
    Order(std::string orderId, Table* table);
    ~Order();
    
    std::string getOrderId() const;
    Table* getTable() const;
    const std::vector<OrderItem*>& getItems() const;
    double getTotalAmount() const;
    std::time_t getOrderTime() const;
    OrderStatus getStatus() const;
    
    void addItem(MenuItem* menuItem, int quantity);
    void removeItem(const std::string& itemId);
    void updateItemQuantity(const std::string& itemId, int quantity);
    void setStatus(OrderStatus status);
    void calculateTotal();
    void displayInfo() const;
};

#endif 