#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

#include <string>
#include <vector>
#include "MenuItem.hpp"

class Restaurant {
private:
    std::string restaurantId;
    std::string name;
    std::string cuisine;
    std::string address;
    std::vector<MenuItem*> menu;
    bool isOpen;

public:
    Restaurant(std::string restaurantId, std::string name, 
              std::string cuisine, std::string address);
    ~Restaurant();
    
    std::string getRestaurantId() const;
    std::string getName() const;
    std::string getCuisine() const;
    std::string getAddress() const;
    bool getIsOpen() const;
    
    void addMenuItem(MenuItem* item);
    void removeMenuItem(MenuItem* item);
    MenuItem* findMenuItem(const std::string& itemId) const;
    void setOpen(bool status);
    void displayInfo() const;
    void displayMenu() const;
};

#endif 