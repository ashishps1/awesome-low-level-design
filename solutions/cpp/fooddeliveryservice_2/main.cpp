// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class MenuItem;
class Restaurant;
class User;
class Order;
class DeliveryService;

// ===== MenuItem.hpp =====
class MenuItem {
private:
    string itemId;
    string name;
    string description;
    double price;
    bool available;

public:
    MenuItem(string itemId, string name, string description, double price);
    
    string getItemId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    bool isAvailable() const;
    
    void setAvailable(bool status);
    void displayInfo() const;
};

// ===== Restaurant.hpp =====
class Restaurant {
private:
    string restaurantId;
    string name;
    string cuisine;
    string address;
    vector<MenuItem*> menu;
    bool isOpen;

public:
    Restaurant(string restaurantId, string name, 
              string cuisine, string address);
    ~Restaurant();
    
    string getRestaurantId() const;
    string getName() const;
    string getCuisine() const;
    string getAddress() const;
    bool getIsOpen() const;
    
    void addMenuItem(MenuItem* item);
    void removeMenuItem(MenuItem* item);
    MenuItem* findMenuItem(const string& itemId) const;
    void setOpen(bool status);
    void displayInfo() const;
    void displayMenu() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string name;
    string email;
    string phone;
    string address;

public:
    User(string userId, string name, string email, 
         string phone, string address);
    
    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getAddress() const;
    void displayInfo() const;
};

// ===== Order.hpp =====
enum class OrderStatus {
    PLACED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    string orderId;
    User* user;
    Restaurant* restaurant;
    map<MenuItem*, int> items;  // item and quantity
    OrderStatus status;
    double totalAmount;
    string timestamp;

public:
    Order(string orderId, User* user, Restaurant* restaurant);
    
    string getOrderId() const;
    User* getUser() const;
    Restaurant* getRestaurant() const;
    OrderStatus getStatus() const;
    double getTotalAmount() const;
    string getTimestamp() const;
    
    void addItem(MenuItem* item, int quantity);
    void setStatus(OrderStatus status);
    void calculateTotal();
    void displayInfo() const;
};

// ===== DeliveryService.hpp =====
class DeliveryService {
private:
    vector<User*> users;
    vector<Restaurant*> restaurants;
    vector<Order*> orders;
    int orderIdCounter;

public:
    DeliveryService();
    ~DeliveryService();
    
    void addUser(User* user);
    void addRestaurant(Restaurant* restaurant);
    
    Order* createOrder(string userId, string restaurantId);
    bool addItemToOrder(string orderId, string itemId, int quantity);
    bool updateOrderStatus(string orderId, OrderStatus status);
    
    void displayAllRestaurants() const;
    void displayRestaurantMenu(string restaurantId) const;
    void displayOrderHistory(string userId) const;
    void displayOrderDetails(string orderId) const;
    
private:
    User* findUser(const string& userId) const;
    Restaurant* findRestaurant(const string& restaurantId) const;
    Order* findOrder(const string& orderId) const;
    string generateOrderId();
};

// ===== DeliveryService.cpp =====
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

Order* DeliveryService::createOrder(string userId, string restaurantId) {
    User* user = findUser(userId);
    Restaurant* restaurant = findRestaurant(restaurantId);
    
    if (!user || !restaurant || !restaurant->getIsOpen()) return nullptr;
    
    Order* order = new Order(generateOrderId(), user, restaurant);
    orders.push_back(order);
    return order;
}

bool DeliveryService::addItemToOrder(string orderId, string itemId, int quantity) {
    Order* order = findOrder(orderId);
    if (!order || order->getStatus() != OrderStatus::PLACED) return false;
    
    MenuItem* item = order->getRestaurant()->findMenuItem(itemId);
    if (!item || !item->isAvailable()) return false;
    
    order->addItem(item, quantity);
    return true;
}

bool DeliveryService::updateOrderStatus(string orderId, OrderStatus status) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->setStatus(status);
    return true;
}

void DeliveryService::displayAllRestaurants() const {
    cout << "\nAvailable Restaurants:" << endl;
    for (const auto& restaurant : restaurants) {
        restaurant->displayInfo();
        cout << "------------------------" << endl;
    }
}

void DeliveryService::displayRestaurantMenu(string restaurantId) const {
    Restaurant* restaurant = findRestaurant(restaurantId);
    if (restaurant) {
        restaurant->displayInfo();
        restaurant->displayMenu();
    }
}

void DeliveryService::displayOrderHistory(string userId) const {
    for (const auto& order : orders) {
        if (order->getUser()->getUserId() == userId) {
            order->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void DeliveryService::displayOrderDetails(string orderId) const {
    Order* order = findOrder(orderId);
    if (order) {
        order->displayInfo();
    }
}

User* DeliveryService::findUser(const string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Restaurant* DeliveryService::findRestaurant(const string& restaurantId) const {
    for (auto restaurant : restaurants) {
        if (restaurant->getRestaurantId() == restaurantId) return restaurant;
    }
    return nullptr;
}

Order* DeliveryService::findOrder(const string& orderId) const {
    for (auto order : orders) {
        if (order->getOrderId() == orderId) return order;
    }
    return nullptr;
}

string DeliveryService::generateOrderId() {
    return "ORD" + to_string(orderIdCounter++);
} 

// ===== MenuItem.cpp =====
MenuItem::MenuItem(string itemId, string name, 
                  string description, double price)
    : itemId(itemId), name(name), description(description), 
      price(price), available(true) {}

string MenuItem::getItemId() const { return itemId; }
string MenuItem::getName() const { return name; }
string MenuItem::getDescription() const { return description; }
double MenuItem::getPrice() const { return price; }
bool MenuItem::isAvailable() const { return available; }

void MenuItem::setAvailable(bool status) {
    available = status;
}

void MenuItem::displayInfo() const {
    cout << "Item: " << name << " (ID: " << itemId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "Status: " << (available ? "Available" : "Not Available") << endl;
} 

// ===== Order.cpp =====
Order::Order(string orderId, User* user, Restaurant* restaurant)
    : orderId(orderId), user(user), restaurant(restaurant), 
      status(OrderStatus::PLACED), totalAmount(0.0) {
    // Get current timestamp
    auto now = time(nullptr);
    timestamp = ctime(&now);
}

string Order::getOrderId() const { return orderId; }
User* Order::getUser() const { return user; }
Restaurant* Order::getRestaurant() const { return restaurant; }
OrderStatus Order::getStatus() const { return status; }
double Order::getTotalAmount() const { return totalAmount; }
string Order::getTimestamp() const { return timestamp; }

void Order::addItem(MenuItem* item, int quantity) {
    if (item && quantity > 0) {
        items[item] = quantity;
        calculateTotal();
    }
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& pair : items) {
        totalAmount += pair.first->getPrice() * pair.second;
    }
}

void Order::displayInfo() const {
    cout << "\nOrder Details:" << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Customer: " << user->getName() << endl;
    cout << "Restaurant: " << restaurant->getName() << endl;
    cout << "Status: ";
    switch (status) {
        case OrderStatus::PLACED: cout << "Placed"; break;
        case OrderStatus::PREPARING: cout << "Preparing"; break;
        case OrderStatus::OUT_FOR_DELIVERY: cout << "Out for Delivery"; break;
        case OrderStatus::DELIVERED: cout << "Delivered"; break;
        case OrderStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
    
    cout << "\nOrdered Items:" << endl;
    for (const auto& pair : items) {
        cout << pair.first->getName() << " x " << pair.second 
                  << " = $" << fixed << setprecision(2)
                  << pair.first->getPrice() * pair.second << endl;
    }
    
    cout << "\nTotal Amount: $" << fixed << setprecision(2) 
              << totalAmount << endl;
    cout << "Order Time: " << timestamp;
} 

// ===== Restaurant.cpp =====
Restaurant::Restaurant(string restaurantId, string name, 
                      string cuisine, string address)
    : restaurantId(restaurantId), name(name), cuisine(cuisine), 
      address(address), isOpen(true) {}

Restaurant::~Restaurant() {
    for (auto item : menu) {
        delete item;
    }
}

string Restaurant::getRestaurantId() const { return restaurantId; }
string Restaurant::getName() const { return name; }
string Restaurant::getCuisine() const { return cuisine; }
string Restaurant::getAddress() const { return address; }
bool Restaurant::getIsOpen() const { return isOpen; }

void Restaurant::addMenuItem(MenuItem* item) {
    menu.push_back(item);
}

void Restaurant::removeMenuItem(MenuItem* item) {
    auto it = find(menu.begin(), menu.end(), item);
    if (it != menu.end()) {
        menu.erase(it);
    }
}

MenuItem* Restaurant::findMenuItem(const string& itemId) const {
    for (auto item : menu) {
        if (item->getItemId() == itemId) return item;
    }
    return nullptr;
}

void Restaurant::setOpen(bool status) {
    isOpen = status;
}

void Restaurant::displayInfo() const {
    cout << "Restaurant: " << name << " (ID: " << restaurantId << ")" << endl;
    cout << "Cuisine: " << cuisine << endl;
    cout << "Address: " << address << endl;
    cout << "Status: " << (isOpen ? "Open" : "Closed") << endl;
}

void Restaurant::displayMenu() const {
    cout << "\nMenu Items:" << endl;
    for (const auto& item : menu) {
        item->displayInfo();
        cout << "------------------------" << endl;
    }
} 

// ===== User.cpp =====
User::User(string userId, string name, string email, 
           string phone, string address)
    : userId(userId), name(name), email(email), phone(phone), address(address) {}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }
string User::getAddress() const { return address; }

void User::displayInfo() const {
    cout << "User: " << name << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
} 

// ===== DeliveryDemo.cpp =====
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
        cout << "\nOrder History for John Doe:" << endl;
        service.displayOrderHistory("U001");
    }
    
    return 0;
} 

