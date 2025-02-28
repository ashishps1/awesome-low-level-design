#include "MenuItem.hpp"
#include <iostream>
#include <iomanip>

MenuItem::MenuItem(std::string itemId, std::string name, 
                  std::string description, double price)
    : itemId(itemId), name(name), description(description), 
      price(price), available(true) {}

std::string MenuItem::getItemId() const { return itemId; }
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getDescription() const { return description; }
double MenuItem::getPrice() const { return price; }
bool MenuItem::isAvailable() const { return available; }

void MenuItem::setAvailable(bool status) {
    available = status;
}

void MenuItem::displayInfo() const {
    std::cout << "Item: " << name << " (ID: " << itemId << ")" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "Status: " << (available ? "Available" : "Not Available") << std::endl;
} 