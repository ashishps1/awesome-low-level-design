// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class MenuItem;
class OrderItem;
class Table;
class Order;
class RestaurantSystem;

// ===== MenuItem.hpp =====
enum class Category {
    APPETIZER,
    MAIN_COURSE,
    DESSERT,
    BEVERAGE
};

class MenuItem {
private:
    string itemId;
    string name;
    string description;
    double price;
    Category category;
    bool available;

public:
    MenuItem(string itemId, string name, string description,
            double price, Category category);
    
    string getItemId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    Category getCategory() const;
    bool isAvailable() const;
    
    void setPrice(double price);
    void setAvailable(bool status);
    void displayInfo() const;
};

// ===== OrderItem.hpp =====
class OrderItem {
private:
    MenuItem* menuItem;
    int quantity;
    double subtotal;

public:
    OrderItem(MenuItem* menuItem, int quantity);
    
    MenuItem* getMenuItem() const;
    int getQuantity() const;
    double getSubtotal() const;
    
    void updateQuantity(int quantity);
    void displayInfo() const;
};

// ===== Table.hpp =====
enum class TableStatus {
    AVAILABLE,
    OCCUPIED,
    RESERVED
};

class Table {
private:
    int tableNumber;
    int capacity;
    TableStatus status;

public:
    Table(int tableNumber, int capacity);
    
    int getTableNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;
    
    void setStatus(TableStatus status);
    void displayInfo() const;
};

// ===== Order.hpp =====
enum class OrderStatus {
    PENDING,
    PREPARING,
    READY,
    SERVED,
    PAID
};

class Order {
private:
    string orderId;
    Table* table;
    vector<OrderItem*> items;
    double totalAmount;
    time_t orderTime;
    OrderStatus status;

public:
    Order(string orderId, Table* table);
    ~Order();
    
    string getOrderId() const;
    Table* getTable() const;
    const vector<OrderItem*>& getItems() const;
    double getTotalAmount() const;
    time_t getOrderTime() const;
    OrderStatus getStatus() const;
    
    void addItem(MenuItem* menuItem, int quantity);
    void removeItem(const string& itemId);
    void updateItemQuantity(const string& itemId, int quantity);
    void setStatus(OrderStatus status);
    void calculateTotal();
    void displayInfo() const;
};

// ===== RestaurantSystem.hpp =====
class RestaurantSystem {
private:
    vector<MenuItem*> menu;
    vector<Table*> tables;
    vector<Order*> orders;
    int orderIdCounter;

public:
    RestaurantSystem();
    ~RestaurantSystem();
    
    // Menu management
    MenuItem* addMenuItem(const string& name, const string& description,
                        double price, Category category);
    void removeMenuItem(const string& itemId);
    void updateItemAvailability(const string& itemId, bool available);
    
    // Table management
    Table* addTable(int capacity);
    void updateTableStatus(int tableNumber, TableStatus status);
    
    // Order management
    Order* createOrder(int tableNumber);
    bool addToOrder(const string& orderId, const string& itemId, int quantity);
    bool updateOrderItem(const string& orderId, const string& itemId, int quantity);
    bool updateOrderStatus(const string& orderId, OrderStatus status);
    
    // Display functions
    void displayMenu() const;
    void displayTables() const;
    void displayOrders() const;
    void displayOrder(const string& orderId) const;

private:
    MenuItem* findMenuItem(const string& itemId) const;
    Table* findTable(int tableNumber) const;
    Order* findOrder(const string& orderId) const;
    string generateOrderId();
};

// ===== MenuItem.cpp =====
MenuItem::MenuItem(string itemId, string name, string description,
                  double price, Category category)
    : itemId(itemId), name(name), description(description),
      price(price), category(category), available(true) {}

string MenuItem::getItemId() const { return itemId; }
string MenuItem::getName() const { return name; }
string MenuItem::getDescription() const { return description; }
double MenuItem::getPrice() const { return price; }
Category MenuItem::getCategory() const { return category; }
bool MenuItem::isAvailable() const { return available; }

void MenuItem::setPrice(double price) {
    if (price > 0) {
        this->price = price;
    }
}

void MenuItem::setAvailable(bool status) {
    available = status;
}

void MenuItem::displayInfo() const {
    cout << name << " (ID: " << itemId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "Category: ";
    switch (category) {
        case Category::APPETIZER: cout << "Appetizer"; break;
        case Category::MAIN_COURSE: cout << "Main Course"; break;
        case Category::DESSERT: cout << "Dessert"; break;
        case Category::BEVERAGE: cout << "Beverage"; break;
    }
    cout << endl;
    cout << "Status: " << (available ? "Available" : "Not Available") << endl;
} 

// ===== Order.cpp =====
Order::Order(string orderId, Table* table)
    : orderId(orderId), table(table), totalAmount(0.0), status(OrderStatus::PENDING) {
    orderTime = time(nullptr);
}

Order::~Order() {
    for (auto item : items) {
        delete item;
    }
}

string Order::getOrderId() const { return orderId; }
Table* Order::getTable() const { return table; }
const vector<OrderItem*>& Order::getItems() const { return items; }
double Order::getTotalAmount() const { return totalAmount; }
time_t Order::getOrderTime() const { return orderTime; }
OrderStatus Order::getStatus() const { return status; }

void Order::addItem(MenuItem* menuItem, int quantity) {
    if (!menuItem || !menuItem->isAvailable()) return;
    
    // Check if item already exists
    auto it = find_if(items.begin(), items.end(),
        [menuItem](OrderItem* item) { return item->getMenuItem() == menuItem; });
    
    if (it != items.end()) {
        (*it)->updateQuantity((*it)->getQuantity() + quantity);
    } else {
        items.push_back(new OrderItem(menuItem, quantity));
    }
    
    calculateTotal();
}

void Order::removeItem(const string& itemId) {
    auto it = find_if(items.begin(), items.end(),
        [itemId](OrderItem* item) { return item->getMenuItem()->getItemId() == itemId; });
    
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        calculateTotal();
    }
}

void Order::updateItemQuantity(const string& itemId, int quantity) {
    auto it = find_if(items.begin(), items.end(),
        [itemId](OrderItem* item) { return item->getMenuItem()->getItemId() == itemId; });
    
    if (it != items.end()) {
        if (quantity <= 0) {
            removeItem(itemId);
        } else {
            (*it)->updateQuantity(quantity);
            calculateTotal();
        }
    }
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item->getSubtotal();
    }
}

void Order::displayInfo() const {
    cout << "\nOrder Details:" << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Table: " << table->getTableNumber() << endl;
    cout << "Time: " << ctime(&orderTime);
    cout << "Status: ";
    switch (status) {
        case OrderStatus::PENDING: cout << "Pending"; break;
        case OrderStatus::PREPARING: cout << "Preparing"; break;
        case OrderStatus::READY: cout << "Ready"; break;
        case OrderStatus::SERVED: cout << "Served"; break;
        case OrderStatus::PAID: cout << "Paid"; break;
    }
    cout << endl;
    
    cout << "\nItems:" << endl;
    for (const auto& item : items) {
        item->displayInfo();
    }
    cout << "------------------------" << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
} 

// ===== OrderItem.cpp =====
OrderItem::OrderItem(MenuItem* menuItem, int quantity)
    : menuItem(menuItem), quantity(quantity) {
    subtotal = menuItem->getPrice() * quantity;
}

MenuItem* OrderItem::getMenuItem() const { return menuItem; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getSubtotal() const { return subtotal; }

void OrderItem::updateQuantity(int quantity) {
    if (quantity > 0) {
        this->quantity = quantity;
        subtotal = menuItem->getPrice() * quantity;
    }
}

void OrderItem::displayInfo() const {
    cout << menuItem->getName() << " x " << quantity 
              << " = $" << fixed << setprecision(2) << subtotal << endl;
} 

// ===== RestaurantSystem.cpp =====
RestaurantSystem::RestaurantSystem() : orderIdCounter(1) {}

RestaurantSystem::~RestaurantSystem() {
    for (auto item : menu) delete item;
    for (auto table : tables) delete table;
    for (auto order : orders) delete order;
}

MenuItem* RestaurantSystem::addMenuItem(const string& name, const string& description,
                                      double price, Category category) {
    string itemId = "ITEM" + to_string(menu.size() + 1);
    MenuItem* item = new MenuItem(itemId, name, description, price, category);
    menu.push_back(item);
    return item;
}

void RestaurantSystem::removeMenuItem(const string& itemId) {
    auto it = find_if(menu.begin(), menu.end(),
        [itemId](MenuItem* item) { return item->getItemId() == itemId; });
    
    if (it != menu.end()) {
        delete *it;
        menu.erase(it);
    }
}

void RestaurantSystem::updateItemAvailability(const string& itemId, bool available) {
    if (MenuItem* item = findMenuItem(itemId)) {
        item->setAvailable(available);
    }
}

Table* RestaurantSystem::addTable(int capacity) {
    int tableNumber = tables.size() + 1;
    Table* table = new Table(tableNumber, capacity);
    tables.push_back(table);
    return table;
}

void RestaurantSystem::updateTableStatus(int tableNumber, TableStatus status) {
    if (Table* table = findTable(tableNumber)) {
        table->setStatus(status);
    }
}

Order* RestaurantSystem::createOrder(int tableNumber) {
    Table* table = findTable(tableNumber);
    if (!table || table->getStatus() != TableStatus::AVAILABLE) return nullptr;
    
    string orderId = generateOrderId();
    Order* order = new Order(orderId, table);
    orders.push_back(order);
    table->setStatus(TableStatus::OCCUPIED);
    return order;
}

bool RestaurantSystem::addToOrder(const string& orderId, const string& itemId, int quantity) {
    Order* order = findOrder(orderId);
    MenuItem* item = findMenuItem(itemId);
    
    if (!order || !item) return false;
    
    order->addItem(item, quantity);
    return true;
}

bool RestaurantSystem::updateOrderItem(const string& orderId, const string& itemId, int quantity) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->updateItemQuantity(itemId, quantity);
    return true;
}

bool RestaurantSystem::updateOrderStatus(const string& orderId, OrderStatus status) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->setStatus(status);
    if (status == OrderStatus::PAID) {
        order->getTable()->setStatus(TableStatus::AVAILABLE);
    }
    return true;
}

void RestaurantSystem::displayMenu() const {
    cout << "\n=== Restaurant Menu ===" << endl;
    for (const auto& item : menu) {
        item->displayInfo();
        cout << "------------------------" << endl;
    }
}

void RestaurantSystem::displayTables() const {
    cout << "\n=== Tables Status ===" << endl;
    for (const auto& table : tables) {
        table->displayInfo();
        cout << "------------------------" << endl;
    }
}

void RestaurantSystem::displayOrders() const {
    cout << "\n=== Current Orders ===" << endl;
    for (const auto& order : orders) {
        order->displayInfo();
    }
}

void RestaurantSystem::displayOrder(const string& orderId) const {
    if (Order* order = findOrder(orderId)) {
        order->displayInfo();
    }
}

MenuItem* RestaurantSystem::findMenuItem(const string& itemId) const {
    auto it = find_if(menu.begin(), menu.end(),
        [itemId](MenuItem* item) { return item->getItemId() == itemId; });
    return it != menu.end() ? *it : nullptr;
}

Table* RestaurantSystem::findTable(int tableNumber) const {
    auto it = find_if(tables.begin(), tables.end(),
        [tableNumber](Table* table) { return table->getTableNumber() == tableNumber; });
    return it != tables.end() ? *it : nullptr;
}

Order* RestaurantSystem::findOrder(const string& orderId) const {
    auto it = find_if(orders.begin(), orders.end(),
        [orderId](Order* order) { return order->getOrderId() == orderId; });
    return it != orders.end() ? *it : nullptr;
}

string RestaurantSystem::generateOrderId() {
    return "ORD" + to_string(orderIdCounter++);
} 

// ===== Table.cpp =====
Table::Table(int tableNumber, int capacity)
    : tableNumber(tableNumber), capacity(capacity), status(TableStatus::AVAILABLE) {}

int Table::getTableNumber() const { return tableNumber; }
int Table::getCapacity() const { return capacity; }
TableStatus Table::getStatus() const { return status; }

void Table::setStatus(TableStatus status) {
    this->status = status;
}

void Table::displayInfo() const {
    cout << "Table " << tableNumber << endl;
    cout << "Capacity: " << capacity << " persons" << endl;
    cout << "Status: ";
    switch (status) {
        case TableStatus::AVAILABLE: cout << "Available"; break;
        case TableStatus::OCCUPIED: cout << "Occupied"; break;
        case TableStatus::RESERVED: cout << "Reserved"; break;
    }
    cout << endl;
} 

// ===== RestaurantDemo.cpp =====
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
    
    cout << "Initial restaurant status:" << endl;
    restaurant.displayMenu();
    restaurant.displayTables();
    
    // Create an order
    Order* order1 = restaurant.createOrder(1);  // Order for table 1
    if (order1) {
        cout << "\nCreated new order: " << order1->getOrderId() << endl;
        
        // Add items to order
        restaurant.addToOrder(order1->getOrderId(), burger->getItemId(), 2);
        restaurant.addToOrder(order1->getOrderId(), fries->getItemId(), 1);
        restaurant.addToOrder(order1->getOrderId(), soda->getItemId(), 2);
        
        // Display order
        restaurant.displayOrder(order1->getOrderId());
        
        // Update order status
        cout << "\nUpdating order status..." << endl;
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::PREPARING);
        this_thread::sleep_for(chrono::seconds(1));
        
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::READY);
        this_thread::sleep_for(chrono::seconds(1));
        
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::SERVED);
        
        // Update order items
        cout << "\nAdding dessert to order..." << endl;
        restaurant.addToOrder(order1->getOrderId(), cake->getItemId(), 2);
        
        // Display final order
        restaurant.displayOrder(order1->getOrderId());
        
        // Complete order
        cout << "\nCompleting order..." << endl;
        restaurant.updateOrderStatus(order1->getOrderId(), OrderStatus::PAID);
    }
    
    // Display final restaurant status
    cout << "\nFinal restaurant status:" << endl;
    restaurant.displayTables();
    restaurant.displayOrders();
    
    return 0;
} 

