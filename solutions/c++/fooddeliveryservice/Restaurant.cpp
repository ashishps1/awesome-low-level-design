#include "Restaurant.hpp"
#include <iostream>
#include <algorithm>

Restaurant::Restaurant(std::string restaurantId, std::string name, 
                      std::string cuisine, std::string address)
    : restaurantId(restaurantId), name(name), cuisine(cuisine), 
      address(address), isOpen(true) {}

Restaurant::~Restaurant() {
    for (auto item : menu) {
        delete item;
    }
}

std::string Restaurant::getRestaurantId() const { return restaurantId; }
std::string Restaurant::getName() const { return name; }
std::string Restaurant::getCuisine() const { return cuisine; }
std::string Restaurant::getAddress() const { return address; }
bool Restaurant::getIsOpen() const { return isOpen; }

void Restaurant::addMenuItem(MenuItem* item) {
    menu.push_back(item);
}

void Restaurant::removeMenuItem(MenuItem* item) {
    auto it = std::find(menu.begin(), menu.end(), item);
    if (it != menu.end()) {
        menu.erase(it);
    }
}

MenuItem* Restaurant::findMenuItem(const std::string& itemId) const {
    for (auto item : menu) {
        if (item->getItemId() == itemId) return item;
    }
    return nullptr;
}

void Restaurant::setOpen(bool status) {
    isOpen = status;
}

void Restaurant::displayInfo() const {
    std::cout << "Restaurant: " << name << " (ID: " << restaurantId << ")" << std::endl;
    std::cout << "Cuisine: " << cuisine << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Status: " << (isOpen ? "Open" : "Closed") << std::endl;
}

void Restaurant::displayMenu() const {
    std::cout << "\nMenu Items:" << std::endl;
    for (const auto& item : menu) {
        item->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
} 