#ifndef ORDER_ITEM_HPP
#define ORDER_ITEM_HPP

#include "MenuItem.hpp"

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

#endif 