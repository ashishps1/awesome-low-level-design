#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>

class MenuItem {
private:
    std::string itemId;
    std::string name;
    std::string description;
    double price;
    bool available;

public:
    MenuItem(std::string itemId, std::string name, std::string description, double price);
    
    std::string getItemId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    bool isAvailable() const;
    
    void setAvailable(bool status);
    void displayInfo() const;
};

#endif 