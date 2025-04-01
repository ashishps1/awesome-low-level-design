#ifndef RESTAURANT_SYSTEM_HPP
#define RESTAURANT_SYSTEM_HPP

#include <vector>
#include <string>
#include "MenuItem.hpp"
#include "Table.hpp"
#include "Order.hpp"

class RestaurantSystem {
private:
    std::vector<MenuItem*> menu;
    std::vector<Table*> tables;
    std::vector<Order*> orders;
    int orderIdCounter;

public:
    RestaurantSystem();
    ~RestaurantSystem();
    
    // Menu management
    MenuItem* addMenuItem(const std::string& name, const std::string& description,
                        double price, Category category);
    void removeMenuItem(const std::string& itemId);
    void updateItemAvailability(const std::string& itemId, bool available);
    
    // Table management
    Table* addTable(int capacity);
    void updateTableStatus(int tableNumber, TableStatus status);
    
    // Order management
    Order* createOrder(int tableNumber);
    bool addToOrder(const std::string& orderId, const std::string& itemId, int quantity);
    bool updateOrderItem(const std::string& orderId, const std::string& itemId, int quantity);
    bool updateOrderStatus(const std::string& orderId, OrderStatus status);
    
    // Display functions
    void displayMenu() const;
    void displayTables() const;
    void displayOrders() const;
    void displayOrder(const std::string& orderId) const;

private:
    MenuItem* findMenuItem(const std::string& itemId) const;
    Table* findTable(int tableNumber) const;
    Order* findOrder(const std::string& orderId) const;
    std::string generateOrderId();
};

#endif 