#include "ShoppingSystem.hpp"
#include <iostream>

int main() {
    ShoppingSystem shop;
    
    // Add products
    Product* laptop = shop.addProduct("Laptop", "High-performance laptop", 999.99, 10);
    Product* phone = shop.addProduct("Smartphone", "Latest model smartphone", 599.99, 20);
    Product* tablet = shop.addProduct("Tablet", "10-inch tablet", 299.99, 15);
    
    std::cout << "Initial Products:" << std::endl;
    shop.displayProducts();
    
    // Register users
    User* user1 = shop.registerUser("john_doe", "john@email.com", "123 Main St");
    User* user2 = shop.registerUser("jane_smith", "jane@email.com", "456 Oak Ave");
    
    std::cout << "\nRegistered Users:" << std::endl;
    shop.displayUsers();
    
    // Add items to cart
    std::cout << "\nAdding items to John's cart..." << std::endl;
    shop.addToCart(user1->getUserId(), laptop->getProductId(), 1);
    shop.addToCart(user1->getUserId(), phone->getProductId(), 2);
    shop.displayCart(user1->getUserId());
    
    // Update cart
    std::cout << "\nUpdating phone quantity..." << std::endl;
    shop.updateCartItem(user1->getUserId(), phone->getProductId(), 1);
    shop.displayCart(user1->getUserId());
    
    // Place order
    std::cout << "\nPlacing order..." << std::endl;
    Order* order = shop.placeOrder(user1->getUserId());
    if (order) {
        std::cout << "Order placed successfully!" << std::endl;
        order->displayInfo();
        
        // Update order status
        shop.updateOrderStatus(order->getOrderId(), OrderStatus::CONFIRMED);
        shop.updateOrderStatus(order->getOrderId(), OrderStatus::SHIPPED);
        
        std::cout << "\nUpdated order status:" << std::endl;
        order->displayInfo();
    }
    
    // Check updated product stock
    std::cout << "\nUpdated product stock:" << std::endl;
    shop.displayProducts();
    
    return 0;
} 