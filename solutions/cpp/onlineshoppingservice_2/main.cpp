// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Product;
class CartItem;
class Order;
class User;
class Cart;
class ShoppingSystem;

// ===== Product.hpp =====
class Product {
private:
    string productId;
    string name;
    string description;
    double price;
    int stockQuantity;
    bool available;

public:
    Product(string productId, string name, string description, 
            double price, int stockQuantity);
    
    string getProductId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    int getStockQuantity() const;
    bool isAvailable() const;
    
    void setPrice(double newPrice);
    void setStockQuantity(int quantity);
    void setAvailable(bool status);
    bool updateStock(int quantity);
    void displayInfo() const;
};

// ===== CartItem.hpp =====
class CartItem {
private:
    Product* product;
    int quantity;

public:
    CartItem(Product* product, int quantity);
    
    Product* getProduct() const;
    int getQuantity() const;
    double getSubtotal() const;
    
    void setQuantity(int quantity);
    void displayInfo() const;
};

// ===== Order.hpp =====
enum class OrderStatus {
    PENDING,
    CONFIRMED,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    string orderId;
    User* user;
    vector<CartItem*> items;
    double totalAmount;
    time_t orderDate;
    OrderStatus status;

public:
    Order(string orderId, User* user, const vector<CartItem*>& items);
    ~Order();
    
    string getOrderId() const;
    User* getUser() const;
    const vector<CartItem*>& getItems() const;
    double getTotalAmount() const;
    time_t getOrderDate() const;
    OrderStatus getStatus() const;
    
    void setStatus(OrderStatus status);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    string address;
    vector<Order*> orders;
    bool active;

public:
    User(string userId, string username, string email, string address);
    ~User();
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    string getAddress() const;
    bool isActive() const;
    const vector<Order*>& getOrders() const;
    
    void addOrder(Order* order);
    void setActive(bool status);
    void displayInfo() const;
    void displayOrders() const;
};

// ===== Cart.hpp =====
class Cart {
private:
    User* user;
    vector<CartItem*> items;
    double total;

public:
    Cart(User* user);
    ~Cart();
    
    User* getUser() const;
    const vector<CartItem*>& getItems() const;
    double getTotal() const;
    
    bool addItem(Product* product, int quantity);
    bool updateItemQuantity(Product* product, int quantity);
    bool removeItem(Product* product);
    void clear();
    void calculateTotal();
    void displayInfo() const;
};

// ===== ShoppingSystem.hpp =====
class ShoppingSystem {
private:
    vector<User*> users;
    vector<Product*> products;
    vector<Order*> orders;
    map<string, Cart*> userCarts;
    int orderIdCounter;

public:
    ShoppingSystem();
    ~ShoppingSystem();
    
    // User management
    User* registerUser(const string& username, const string& email, 
                      const string& address);
    void removeUser(const string& userId);
    
    // Product management
    Product* addProduct(const string& name, const string& description,
                       double price, int stockQuantity);
    void removeProduct(const string& productId);
    void updateProductStock(const string& productId, int quantity);
    
    // Cart operations
    bool addToCart(const string& userId, const string& productId, int quantity);
    bool updateCartItem(const string& userId, const string& productId, int quantity);
    bool removeFromCart(const string& userId, const string& productId);
    void clearCart(const string& userId);
    
    // Order operations
    Order* placeOrder(const string& userId);
    bool updateOrderStatus(const string& orderId, OrderStatus status);
    
    // Display functions
    void displayProducts() const;
    void displayUsers() const;
    void displayCart(const string& userId) const;
    void displayOrders(const string& userId) const;
    void displayAllOrders() const;
    
private:
    User* findUser(const string& userId) const;
    Product* findProduct(const string& productId) const;
    Order* findOrder(const string& orderId) const;
    Cart* getCart(const string& userId);
    string generateOrderId();
};

// ===== Cart.cpp =====
Cart::Cart(User* user) : user(user), total(0.0) {}

Cart::~Cart() {
    clear();
}

User* Cart::getUser() const { return user; }
const vector<CartItem*>& Cart::getItems() const { return items; }
double Cart::getTotal() const { return total; }

bool Cart::addItem(Product* product, int quantity) {
    if (!product->isAvailable() || quantity <= 0 || 
        quantity > product->getStockQuantity()) {
        return false;
    }

    // Check if product already exists in cart
    for (auto item : items) {
        if (item->getProduct() == product) {
            return updateItemQuantity(product, item->getQuantity() + quantity);
        }
    }

    items.push_back(new CartItem(product, quantity));
    calculateTotal();
    return true;
}

bool Cart::updateItemQuantity(Product* product, int quantity) {
    if (quantity <= 0 || quantity > product->getStockQuantity()) {
        return false;
    }

    for (auto item : items) {
        if (item->getProduct() == product) {
            item->setQuantity(quantity);
            calculateTotal();
            return true;
        }
    }
    return false;
}

bool Cart::removeItem(Product* product) {
    auto it = find_if(items.begin(), items.end(),
        [product](CartItem* item) { return item->getProduct() == product; });
    
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        calculateTotal();
        return true;
    }
    return false;
}

void Cart::clear() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
    total = 0.0;
}

void Cart::calculateTotal() {
    total = 0.0;
    for (const auto& item : items) {
        total += item->getSubtotal();
    }
}

void Cart::displayInfo() const {
    cout << "\nShopping Cart for " << user->getUsername() << ":" << endl;
    cout << "Items:" << endl;
    for (const auto& item : items) {
        item->displayInfo();
    }
    cout << "------------------------" << endl;
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
} 

// ===== CartItem.cpp =====
CartItem::CartItem(Product* product, int quantity)
    : product(product), quantity(quantity) {}

Product* CartItem::getProduct() const { return product; }
int CartItem::getQuantity() const { return quantity; }

double CartItem::getSubtotal() const {
    return product->getPrice() * quantity;
}

void CartItem::setQuantity(int quantity) {
    if (quantity > 0) {
        this->quantity = quantity;
    }
}

void CartItem::displayInfo() const {
    cout << product->getName() << " x " << quantity 
              << " = $" << fixed << setprecision(2) 
              << getSubtotal() << endl;
} 

// ===== Order.cpp =====
Order::Order(string orderId, User* user, const vector<CartItem*>& cartItems)
    : orderId(orderId), user(user), status(OrderStatus::PENDING), totalAmount(0.0) {
    
    // Deep copy cart items
    for (const auto& cartItem : cartItems) {
        items.push_back(new CartItem(cartItem->getProduct(), cartItem->getQuantity()));
        totalAmount += cartItem->getSubtotal();
    }
    
    // Set order date to current time
    orderDate = time(nullptr);
}

Order::~Order() {
    for (auto item : items) {
        delete item;
    }
}

string Order::getOrderId() const { return orderId; }
User* Order::getUser() const { return user; }
const vector<CartItem*>& Order::getItems() const { return items; }
double Order::getTotalAmount() const { return totalAmount; }
time_t Order::getOrderDate() const { return orderDate; }
OrderStatus Order::getStatus() const { return status; }

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::displayInfo() const {
    cout << "\nOrder Details:" << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Customer: " << user->getUsername() << endl;
    cout << "Date: " << ctime(&orderDate);
    cout << "Status: ";
    switch (status) {
        case OrderStatus::PENDING: cout << "Pending"; break;
        case OrderStatus::CONFIRMED: cout << "Confirmed"; break;
        case OrderStatus::SHIPPED: cout << "Shipped"; break;
        case OrderStatus::DELIVERED: cout << "Delivered"; break;
        case OrderStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
    
    cout << "\nItems:" << endl;
    for (const auto& item : items) {
        item->displayInfo();
    }
    cout << "------------------------" << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
} 

// ===== Product.cpp =====
Product::Product(string productId, string name, string description, 
                double price, int stockQuantity)
    : productId(productId), name(name), description(description), 
      price(price), stockQuantity(stockQuantity), available(true) {}

string Product::getProductId() const { return productId; }
string Product::getName() const { return name; }
string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getStockQuantity() const { return stockQuantity; }
bool Product::isAvailable() const { return available; }

void Product::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    }
}

void Product::setStockQuantity(int quantity) {
    if (quantity >= 0) {
        stockQuantity = quantity;
        available = (quantity > 0);
    }
}

void Product::setAvailable(bool status) {
    available = status;
}

bool Product::updateStock(int quantity) {
    if (stockQuantity + quantity >= 0) {
        stockQuantity += quantity;
        available = (stockQuantity > 0);
        return true;
    }
    return false;
}

void Product::displayInfo() const {
    cout << "Product: " << name << " (ID: " << productId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "Stock: " << stockQuantity << endl;
    cout << "Status: " << (available ? "Available" : "Out of Stock") << endl;
} 

// ===== ShoppingSystem.cpp =====
ShoppingSystem::ShoppingSystem() : orderIdCounter(1) {}

ShoppingSystem::~ShoppingSystem() {
    for (auto user : users) delete user;
    for (auto product : products) delete product;
    for (auto order : orders) delete order;
    for (auto& pair : userCarts) delete pair.second;
}

User* ShoppingSystem::registerUser(const string& username, const string& email, 
                                 const string& address) {
    string userId = "U" + to_string(users.size() + 1);
    User* user = new User(userId, username, email, address);
    users.push_back(user);
    return user;
}

void ShoppingSystem::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
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

Product* ShoppingSystem::addProduct(const string& name, const string& description,
                                  double price, int stockQuantity) {
    string productId = "P" + to_string(products.size() + 1);
    Product* product = new Product(productId, name, description, price, stockQuantity);
    products.push_back(product);
    return product;
}

void ShoppingSystem::removeProduct(const string& productId) {
    auto it = find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    
    if (it != products.end()) {
        delete *it;
        products.erase(it);
    }
}

void ShoppingSystem::updateProductStock(const string& productId, int quantity) {
    if (Product* product = findProduct(productId)) {
        product->updateStock(quantity);
    }
}

bool ShoppingSystem::addToCart(const string& userId, const string& productId, int quantity) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->addItem(product, quantity);
}

bool ShoppingSystem::updateCartItem(const string& userId, const string& productId, int quantity) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->updateItemQuantity(product, quantity);
}

bool ShoppingSystem::removeFromCart(const string& userId, const string& productId) {
    User* user = findUser(userId);
    Product* product = findProduct(productId);
    
    if (!user || !product) return false;
    
    Cart* cart = getCart(userId);
    return cart->removeItem(product);
}

void ShoppingSystem::clearCart(const string& userId) {
    if (Cart* cart = getCart(userId)) {
        cart->clear();
    }
}

Order* ShoppingSystem::placeOrder(const string& userId) {
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
    string orderId = generateOrderId();
    Order* order = new Order(orderId, user, cart->getItems());
    orders.push_back(order);
    user->addOrder(order);
    
    // Clear cart after successful order
    cart->clear();
    
    return order;
}

bool ShoppingSystem::updateOrderStatus(const string& orderId, OrderStatus status) {
    if (Order* order = findOrder(orderId)) {
        order->setStatus(status);
        return true;
    }
    return false;
}

void ShoppingSystem::displayProducts() const {
    cout << "\nAvailable Products:" << endl;
    for (const auto& product : products) {
        product->displayInfo();
        cout << "------------------------" << endl;
    }
}

void ShoppingSystem::displayUsers() const {
    cout << "\nRegistered Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void ShoppingSystem::displayCart(const string& userId) const {
    auto it = userCarts.find(userId);
    if (it != userCarts.end()) {
        it->second->displayInfo();
    }
}

void ShoppingSystem::displayOrders(const string& userId) const {
    if (User* user = findUser(userId)) {
        user->displayOrders();
    }
}

void ShoppingSystem::displayAllOrders() const {
    cout << "\nAll Orders:" << endl;
    for (const auto& order : orders) {
        order->displayInfo();
        cout << "------------------------" << endl;
    }
}

User* ShoppingSystem::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Product* ShoppingSystem::findProduct(const string& productId) const {
    auto it = find_if(products.begin(), products.end(),
        [productId](Product* product) { return product->getProductId() == productId; });
    return it != products.end() ? *it : nullptr;
}

Order* ShoppingSystem::findOrder(const string& orderId) const {
    auto it = find_if(orders.begin(), orders.end(),
        [orderId](Order* order) { return order->getOrderId() == orderId; });
    return it != orders.end() ? *it : nullptr;
}

Cart* ShoppingSystem::getCart(const string& userId) {
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

string ShoppingSystem::generateOrderId() {
    return "O" + to_string(orderIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string username, string email, string address)
    : userId(userId), username(username), email(email), address(address), active(true) {}

User::~User() {
    for (auto order : orders) {
        delete order;
    }
}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
string User::getAddress() const { return address; }
bool User::isActive() const { return active; }
const vector<Order*>& User::getOrders() const { return orders; }

void User::addOrder(Order* order) {
    orders.push_back(order);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Address: " << address << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Total Orders: " << orders.size() << endl;
}

void User::displayOrders() const {
    cout << "\nOrder History for " << username << ":" << endl;
    for (const auto& order : orders) {
        order->displayInfo();
        cout << "------------------------" << endl;
    }
} 

// ===== ShoppingDemo.cpp =====
int main() {
    ShoppingSystem shop;
    
    // Add products
    Product* laptop = shop.addProduct("Laptop", "High-performance laptop", 999.99, 10);
    Product* phone = shop.addProduct("Smartphone", "Latest model smartphone", 599.99, 20);
    Product* tablet = shop.addProduct("Tablet", "10-inch tablet", 299.99, 15);
    
    cout << "Initial Products:" << endl;
    shop.displayProducts();
    
    // Register users
    User* user1 = shop.registerUser("john_doe", "john@email.com", "123 Main St");
    User* user2 = shop.registerUser("jane_smith", "jane@email.com", "456 Oak Ave");
    
    cout << "\nRegistered Users:" << endl;
    shop.displayUsers();
    
    // Add items to cart
    cout << "\nAdding items to John's cart..." << endl;
    shop.addToCart(user1->getUserId(), laptop->getProductId(), 1);
    shop.addToCart(user1->getUserId(), phone->getProductId(), 2);
    shop.displayCart(user1->getUserId());
    
    // Update cart
    cout << "\nUpdating phone quantity..." << endl;
    shop.updateCartItem(user1->getUserId(), phone->getProductId(), 1);
    shop.displayCart(user1->getUserId());
    
    // Place order
    cout << "\nPlacing order..." << endl;
    Order* order = shop.placeOrder(user1->getUserId());
    if (order) {
        cout << "Order placed successfully!" << endl;
        order->displayInfo();
        
        // Update order status
        shop.updateOrderStatus(order->getOrderId(), OrderStatus::CONFIRMED);
        shop.updateOrderStatus(order->getOrderId(), OrderStatus::SHIPPED);
        
        cout << "\nUpdated order status:" << endl;
        order->displayInfo();
    }
    
    // Check updated product stock
    cout << "\nUpdated product stock:" << endl;
    shop.displayProducts();
    
    return 0;
} 

