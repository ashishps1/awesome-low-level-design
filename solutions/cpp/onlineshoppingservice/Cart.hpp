#ifndef CART_HPP
#define CART_HPP

#include <vector>
#include "CartItem.hpp"
#include "User.hpp"

class Cart {
private:
    User* user;
    std::vector<CartItem*> items;
    double total;

public:
    Cart(User* user);
    ~Cart();
    
    User* getUser() const;
    const std::vector<CartItem*>& getItems() const;
    double getTotal() const;
    
    bool addItem(Product* product, int quantity);
    bool updateItemQuantity(Product* product, int quantity);
    bool removeItem(Product* product);
    void clear();
    void calculateTotal();
    void displayInfo() const;
};

#endif 