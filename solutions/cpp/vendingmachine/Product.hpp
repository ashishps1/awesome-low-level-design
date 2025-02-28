#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
private:
    std::string productId;
    std::string name;
    double price;
    int quantity;
    bool available;

public:
    Product(std::string productId, std::string name, double price, int quantity = 0);
    
    std::string getProductId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    bool isAvailable() const;
    
    void setPrice(double price);
    void setQuantity(int quantity);
    void setAvailable(bool status);
    void addQuantity(int amount);
    bool removeQuantity(int amount);
    void displayInfo() const;
};

#endif 