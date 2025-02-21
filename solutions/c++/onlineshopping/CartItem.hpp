#ifndef CART_ITEM_HPP
#define CART_ITEM_HPP

#include "Product.hpp"

class CartItem {
private:
    Product* product;
    int quantity;

public:
    CartItem(Product* product, int quantity);
    
    Product* getProduct() const;
    int getQuantity() const;
    double getSubtotal() const;
    
    void setQuantity(int quantity);
    void displayInfo() const;
};

#endif 