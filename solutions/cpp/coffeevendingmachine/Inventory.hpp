#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include "CoffeeType.hpp"

class Inventory {
private:
    std::map<CoffeeType, int> items;

public:
    Inventory();
    
    void addItem(CoffeeType type, int quantity);
    bool hasItem(CoffeeType type);
    void deductItem(CoffeeType type);
    int getQuantity(CoffeeType type) const;
    void display() const;
};

#endif 