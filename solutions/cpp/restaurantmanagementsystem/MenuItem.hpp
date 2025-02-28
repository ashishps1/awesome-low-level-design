#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>

enum class Category {
    APPETIZER,
    MAIN_COURSE,
    DESSERT,
    BEVERAGE
};

class MenuItem {
private:
    std::string itemId;
    std::string name;
    std::string description;
    double price;
    Category category;
    bool available;

public:
    MenuItem(std::string itemId, std::string name, std::string description,
            double price, Category category);
    
    std::string getItemId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    Category getCategory() const;
    bool isAvailable() const;
    
    void setPrice(double price);
    void setAvailable(bool status);
    void displayInfo() const;
};

#endif 