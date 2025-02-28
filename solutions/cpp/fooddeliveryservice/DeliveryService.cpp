#include "DeliveryService.hpp"
#include <iostream>

DeliveryService::DeliveryService() : orderIdCounter(1) {}

DeliveryService::~DeliveryService() {
    for (auto user : users) delete user;
    for (auto restaurant : restaurants) delete restaurant;
    for (auto order : orders) delete order;
}

void DeliveryService::addUser(User* user) {
    users.push_back(user);
}

void DeliveryService::addRestaurant(Restaurant* restaurant) {
    restaurants.push_back(restaurant);
}

Order* DeliveryService::createOrder(std::string userId, std::string restaurantId) {
    User* user = findUser(userId);
    Restaurant* restaurant = findRestaurant(restaurantId);
    
    if (!user || !restaurant || !restaurant->getIsOpen()) return nullptr;
    
    Order* order = new Order(generateOrderId(), user, restaurant);
    orders.push_back(order);
    return order;
}

bool DeliveryService::addItemToOrder(std::string orderId, std::string itemId, int quantity) {
    Order* order = findOrder(orderId);
    if (!order || order->getStatus() != OrderStatus::PLACED) return false;
    
    MenuItem* item = order->getRestaurant()->findMenuItem(itemId);
    if (!item || !item->isAvailable()) return false;
    
    order->addItem(item, quantity);
    return true;
}

bool DeliveryService::updateOrderStatus(std::string orderId, OrderStatus status) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->setStatus(status);
    return true;
}

void DeliveryService::displayAllRestaurants() const {
    std::cout << "\nAvailable Restaurants:" << std::endl;
    for (const auto& restaurant : restaurants) {
        restaurant->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void DeliveryService::displayRestaurantMenu(std::string restaurantId) const {
    Restaurant* restaurant = findRestaurant(restaurantId);
    if (restaurant) {
        restaurant->displayInfo();
        restaurant->displayMenu();
    }
}

void DeliveryService::displayOrderHistory(std::string userId) const {
    for (const auto& order : orders) {
        if (order->getUser()->getUserId() == userId) {
            order->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void DeliveryService::displayOrderDetails(std::string orderId) const {
    Order* order = findOrder(orderId);
    if (order) {
        order->displayInfo();
    }
}

User* DeliveryService::findUser(const std::string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Restaurant* DeliveryService::findRestaurant(const std::string& restaurantId) const {
    for (auto restaurant : restaurants) {
        if (restaurant->getRestaurantId() == restaurantId) return restaurant;
    }
    return nullptr;
}

Order* DeliveryService::findOrder(const std::string& orderId) const {
    for (auto order : orders) {
        if (order->getOrderId() == orderId) return order;
    }
    return nullptr;
}

std::string DeliveryService::generateOrderId() {
    return "ORD" + std::to_string(orderIdCounter++);
} 