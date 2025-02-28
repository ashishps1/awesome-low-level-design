#ifndef DELIVERY_SERVICE_HPP
#define DELIVERY_SERVICE_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Restaurant.hpp"
#include "Order.hpp"

class DeliveryService {
private:
    std::vector<User*> users;
    std::vector<Restaurant*> restaurants;
    std::vector<Order*> orders;
    int orderIdCounter;

public:
    DeliveryService();
    ~DeliveryService();
    
    void addUser(User* user);
    void addRestaurant(Restaurant* restaurant);
    
    Order* createOrder(std::string userId, std::string restaurantId);
    bool addItemToOrder(std::string orderId, std::string itemId, int quantity);
    bool updateOrderStatus(std::string orderId, OrderStatus status);
    
    void displayAllRestaurants() const;
    void displayRestaurantMenu(std::string restaurantId) const;
    void displayOrderHistory(std::string userId) const;
    void displayOrderDetails(std::string orderId) const;
    
private:
    User* findUser(const std::string& userId) const;
    Restaurant* findRestaurant(const std::string& restaurantId) const;
    Order* findOrder(const std::string& orderId) const;
    std::string generateOrderId();
};

#endif 