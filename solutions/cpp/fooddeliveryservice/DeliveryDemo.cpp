#include "DeliveryService.hpp"
#include <iostream>

int main() {
    DeliveryService service;
    
    // Create users
    User* user1 = new User("U001", "John Doe", "john@example.com", 
                          "+1-555-0123", "123 Main St");
    service.addUser(user1);
    
    // Create restaurants
    Restaurant* restaurant1 = new Restaurant("R001", "Pizza Palace", 
                                           "Italian", "456 Oak Ave");
    
    // Add menu items
    MenuItem* item1 = new MenuItem("I001", "Margherita Pizza", 
                                 "Classic tomato and mozzarella", 12.99);
    MenuItem* item2 = new MenuItem("I002", "Pepperoni Pizza", 
                                 "Spicy pepperoni with cheese", 14.99);
    restaurant1->addMenuItem(item1);
    restaurant1->addMenuItem(item2);
    
    service.addRestaurant(restaurant1);
    
    // Display available restaurants
    service.displayAllRestaurants();
    
    // Create an order
    Order* order = service.createOrder("U001", "R001");
    if (order) {
        service.addItemToOrder(order->getOrderId(), "I001", 2);  // 2 Margherita pizzas
        service.addItemToOrder(order->getOrderId(), "I002", 1);  // 1 Pepperoni pizza
        
        // Display order details
        service.displayOrderDetails(order->getOrderId());
        
        // Update order status
        service.updateOrderStatus(order->getOrderId(), OrderStatus::PREPARING);
        service.updateOrderStatus(order->getOrderId(), OrderStatus::OUT_FOR_DELIVERY);
        service.updateOrderStatus(order->getOrderId(), OrderStatus::DELIVERED);
        
        // Display order history
        std::cout << "\nOrder History for John Doe:" << std::endl;
        service.displayOrderHistory("U001");
    }
    
    return 0;
} 