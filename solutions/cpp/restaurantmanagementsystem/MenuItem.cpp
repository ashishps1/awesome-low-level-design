#include "MenuItem.hpp"
#include <iostream>
#include <iomanip>

MenuItem::MenuItem(std::string itemId, std::string name, std::string description,
                  double price, Category category)
    : itemId(itemId), name(name), description(description),
      price(price), category(category), available(true) {}

std::string MenuItem::getItemId() const { return itemId; }
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getDescription() const { return description; }
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
    std::cout << name << " (ID: " << itemId << ")" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "Category: ";
    switch (category) {
        case Category::APPETIZER: std::cout << "Appetizer"; break;
        case Category::MAIN_COURSE: std::cout << "Main Course"; break;
        case Category::DESSERT: std::cout << "Dessert"; break;
        case Category::BEVERAGE: std::cout << "Beverage"; break;
    }
    std::cout << std::endl;
    std::cout << "Status: " << (available ? "Available" : "Not Available") << std::endl;
} 