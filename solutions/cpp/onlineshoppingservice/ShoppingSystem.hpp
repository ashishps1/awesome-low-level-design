#ifndef SHOPPING_SYSTEM_HPP
#define SHOPPING_SYSTEM_HPP

#include <vector>
#include <string>
#include <map>
#include "User.hpp"
#include "Product.hpp"
#include "Cart.hpp"
#include "Order.hpp"

class ShoppingSystem {
private:
    std::vector<User*> users;
    std::vector<Product*> products;
    std::vector<Order*> orders;
    std::map<std::string, Cart*> userCarts;
    int orderIdCounter;

public:
    ShoppingSystem();
    ~ShoppingSystem();
    
    // User management
    User* registerUser(const std::string& username, const std::string& email, 
                      const std::string& address);
    void removeUser(const std::string& userId);
    
    // Product management
    Product* addProduct(const std::string& name, const std::string& description,
                       double price, int stockQuantity);
    void removeProduct(const std::string& productId);
    void updateProductStock(const std::string& productId, int quantity);
    
    // Cart operations
    bool addToCart(const std::string& userId, const std::string& productId, int quantity);
    bool updateCartItem(const std::string& userId, const std::string& productId, int quantity);
    bool removeFromCart(const std::string& userId, const std::string& productId);
    void clearCart(const std::string& userId);
    
    // Order operations
    Order* placeOrder(const std::string& userId);
    bool updateOrderStatus(const std::string& orderId, OrderStatus status);
    
    // Display functions
    void displayProducts() const;
    void displayUsers() const;
    void displayCart(const std::string& userId) const;
    void displayOrders(const std::string& userId) const;
    void displayAllOrders() const;
    
private:
    User* findUser(const std::string& userId) const;
    Product* findProduct(const std::string& productId) const;
    Order* findOrder(const std::string& orderId) const;
    Cart* getCart(const std::string& userId);
    std::string generateOrderId();
};

#endif 