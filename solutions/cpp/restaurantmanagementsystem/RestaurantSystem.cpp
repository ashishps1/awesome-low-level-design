#include "RestaurantSystem.hpp"
#include <iostream>
#include <algorithm>

RestaurantSystem::RestaurantSystem() : orderIdCounter(1) {}

RestaurantSystem::~RestaurantSystem() {
    for (auto item : menu) delete item;
    for (auto table : tables) delete table;
    for (auto order : orders) delete order;
}

MenuItem* RestaurantSystem::addMenuItem(const std::string& name, const std::string& description,
                                      double price, Category category) {
    std::string itemId = "ITEM" + std::to_string(menu.size() + 1);
    MenuItem* item = new MenuItem(itemId, name, description, price, category);
    menu.push_back(item);
    return item;
}

void RestaurantSystem::removeMenuItem(const std::string& itemId) {
    auto it = std::find_if(menu.begin(), menu.end(),
        [itemId](MenuItem* item) { return item->getItemId() == itemId; });
    
    if (it != menu.end()) {
        delete *it;
        menu.erase(it);
    }
}

void RestaurantSystem::updateItemAvailability(const std::string& itemId, bool available) {
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
    
    std::string orderId = generateOrderId();
    Order* order = new Order(orderId, table);
    orders.push_back(order);
    table->setStatus(TableStatus::OCCUPIED);
    return order;
}

bool RestaurantSystem::addToOrder(const std::string& orderId, const std::string& itemId, int quantity) {
    Order* order = findOrder(orderId);
    MenuItem* item = findMenuItem(itemId);
    
    if (!order || !item) return false;
    
    order->addItem(item, quantity);
    return true;
}

bool RestaurantSystem::updateOrderItem(const std::string& orderId, const std::string& itemId, int quantity) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->updateItemQuantity(itemId, quantity);
    return true;
}

bool RestaurantSystem::updateOrderStatus(const std::string& orderId, OrderStatus status) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    
    order->setStatus(status);
    if (status == OrderStatus::PAID) {
        order->getTable()->setStatus(TableStatus::AVAILABLE);
    }
    return true;
}

void RestaurantSystem::displayMenu() const {
    std::cout << "\n=== Restaurant Menu ===" << std::endl;
    for (const auto& item : menu) {
        item->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void RestaurantSystem::displayTables() const {
    std::cout << "\n=== Tables Status ===" << std::endl;
    for (const auto& table : tables) {
        table->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void RestaurantSystem::displayOrders() const {
    std::cout << "\n=== Current Orders ===" << std::endl;
    for (const auto& order : orders) {
        order->displayInfo();
    }
}

void RestaurantSystem::displayOrder(const std::string& orderId) const {
    if (Order* order = findOrder(orderId)) {
        order->displayInfo();
    }
}

MenuItem* RestaurantSystem::findMenuItem(const std::string& itemId) const {
    auto it = std::find_if(menu.begin(), menu.end(),
        [itemId](MenuItem* item) { return item->getItemId() == itemId; });
    return it != menu.end() ? *it : nullptr;
}

Table* RestaurantSystem::findTable(int tableNumber) const {
    auto it = std::find_if(tables.begin(), tables.end(),
        [tableNumber](Table* table) { return table->getTableNumber() == tableNumber; });
    return it != tables.end() ? *it : nullptr;
}

Order* RestaurantSystem::findOrder(const std::string& orderId) const {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](Order* order) { return order->getOrderId() == orderId; });
    return it != orders.end() ? *it : nullptr;
}

std::string RestaurantSystem::generateOrderId() {
    return "ORD" + std::to_string(orderIdCounter++);
} 