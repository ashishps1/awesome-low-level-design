#include "ShoppingSystem.hpp"
#include <iostream>
#include <algorithm>

ShoppingSystem::ShoppingSystem() : orderIdCounter(1) {}

ShoppingSystem::~ShoppingSystem() {
    for (auto user : users) delete user;
    for (auto product : products) delete product;
    for (auto order : orders) delete order;
    for (auto& pair : userCarts) delete pair.second;
}

User* ShoppingSystem::registerUser(const std::string& username, const std::string& email, 
                                 const std::string& address) {
    std::string userId = "U" + std::to_string(users.size() + 1);
    User* user = new User(userId, username, email, address);
    users.push_back(user);
    return user;
}

void ShoppingSystem::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
        
        // Remove user's cart
        auto cartIt = userCarts.find(userId);
        if (cartIt != userCarts.end()) {
            delete cartIt->second;
            userCarts.erase(cartIt);
        }
    }
}

Product* ShoppingSystem::addProduct(const std::string& name, const std::string& description,
                                  double price, int stockQuantity) {
    std::string productId = "P" + std::to_string(products.size() + 1);
    Product* product = new Product(productId, name, description, price, stockQuantity);
    products.push_back(product);
    return product;
}

void ShoppingSystem::removeProduct(const std::string& productId) {
    auto it = std::find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    
    if (it != products.end()) {
        delete *it;
        products.erase(it);
    }
}

void ShoppingSystem::updateProductStock(const std::string& productId, int quantity) {
    if (Product* product = findProduct(productId)) {
        product->updateStock(quantity);
    }
}

bool ShoppingSystem::addToCart(const std::string& userId, const std::string& productId, int quantity) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->addItem(product, quantity);
}

bool ShoppingSystem::updateCartItem(const std::string& userId, const std::string& productId, int quantity) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->updateItemQuantity(product, quantity);
}

bool ShoppingSystem::removeFromCart(const std::string& userId, const std::string& productId) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->removeItem(product);
}

void ShoppingSystem::clearCart(const std::string& userId) {
    if (Cart* cart = getCart(userId)) {
        cart->clear();
    }
}

Order* ShoppingSystem::placeOrder(const std::string& userId) {
    User* user = findUser(userId);
    Cart* cart = getCart(userId);
    
    if (!user || !cart || cart->getItems().empty()) return nullptr;
    
    // Check stock availability and update stock
    for (const auto& item : cart->getItems()) {
        Product* product = item->getProduct();
        if (!product->updateStock(-item->getQuantity())) {
            return nullptr;
        }
    }
    
    // Create order
    std::string orderId = generateOrderId();
    Order* order = new Order(orderId, user, cart->getItems());
    orders.push_back(order);
    user->addOrder(order);
    
    // Clear cart after successful order
    cart->clear();
    
    return order;
}

bool ShoppingSystem::updateOrderStatus(const std::string& orderId, OrderStatus status) {
    if (Order* order = findOrder(orderId)) {
        order->setStatus(status);
        return true;
    }
    return false;
}

void ShoppingSystem::displayProducts() const {
    std::cout << "\nAvailable Products:" << std::endl;
    for (const auto& product : products) {
        product->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void ShoppingSystem::displayUsers() const {
    std::cout << "\nRegistered Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void ShoppingSystem::displayCart(const std::string& userId) const {
    auto it = userCarts.find(userId);
    if (it != userCarts.end()) {
        it->second->displayInfo();
    }
}

void ShoppingSystem::displayOrders(const std::string& userId) const {
    if (User* user = findUser(userId)) {
        user->displayOrders();
    }
}

void ShoppingSystem::displayAllOrders() const {
    std::cout << "\nAll Orders:" << std::endl;
    for (const auto& order : orders) {
        order->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

User* ShoppingSystem::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Product* ShoppingSystem::findProduct(const std::string& productId) const {
    auto it = std::find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    return it != products.end() ? *it : nullptr;
}

Order* ShoppingSystem::findOrder(const std::string& orderId) const {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](Order* order) { return order->getOrderId() == orderId; });
    return it != orders.end() ? *it : nullptr;
}

Cart* ShoppingSystem::getCart(const std::string& userId) {
    auto it = userCarts.find(userId);
    if (it == userCarts.end()) {
        User* user = findUser(userId);
        if (!user) return nullptr;
        
        Cart* cart = new Cart(user);
        userCarts[userId] = cart;
        return cart;
    }
    return it->second;
}

std::string ShoppingSystem::generateOrderId() {
    return "O" + std::to_string(orderIdCounter++);
} 