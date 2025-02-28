#include "RestaurantSystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    RestaurantSystem restaurant;
    
    // Add menu items
    MenuItem* burger = restaurant.addMenuItem("Burger", "Classic beef burger", 12.99, Category::MAIN_COURSE);
    MenuItem* fries = restaurant.addMenuItem("Fries", "Crispy french fries", 4.99, Category::APPETIZER);
    MenuItem* salad = restaurant.addMenuItem("Salad", "Fresh garden salad", 8.99, Category::APPETIZER);
    MenuItem* soda = restaurant.addMenuItem("Soda", "Carbonated drink", 2.99, Category::BEVERAGE);
    MenuItem* cake = restaurant.addMenuItem("Cake", "Chocolate cake", 6.99, Category::DESSERT);
    
    // Add tables
    restaurant.addTable(2);  // Table 1: 2 seats
    restaurant.addTable(4);  // Table 2: 4 seats
    restaurant.addTable(6);  // Table 3: 6 seats
    
    std::cout << "Initial restaurant status:" << std::endl;
    restaurant.displayMenu();
    restaurant.displayTables();
    
    // Create an order
    Order* order1 = restaurant.createOrder(1);  // Order for table 1
    if (order1) {
        std::cout << "\nCreated new order: " << order1->getOrderId() << std::endl;
        
        // Add items to order
        restaurant.addToOrder(order1->getOrderId(), burger->getItemId(), 2);
        restaurant.addToOrder(order1->getOrderId(), fries->getItemId(), 1);
        restaurant.addToOrder(order1->getOrderId(), soda->getItemId(), 2);
        
        // Display order
        restaurant.displayOrder(order1->getOrderId());
        
        // Update order status
        std::cout << "\nUpdating order status..." << std::endl;
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::PREPARING);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::READY);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::SERVED);
        
        // Update order items
        std::cout << "\nAdding dessert to order..." << std::endl;
        restaurant.addToOrder(order1->getOrderId(), cake->getItemId(), 2);
        
        // Display final order
        restaurant.displayOrder(order1->getOrderId());
        
        // Complete order
        std::cout << "\nCompleting order..." << std::endl;
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::PAID);
    }
    
    // Display final restaurant status
    std::cout << "\nFinal restaurant status:" << std::endl;
    restaurant.displayTables();
    restaurant.displayOrders();
    
    return 0;
} 