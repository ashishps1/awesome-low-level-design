#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
private:
    std::string productId;
    std::string name;
    std::string description;
    double price;
    int stockQuantity;
    bool available;

public:
    Product(std::string productId, std::string name, std::string description, 
            double price, int stockQuantity);
    
    std::string getProductId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getStockQuantity() const;
    bool isAvailable() const;
    
    void setPrice(double newPrice);
    void setStockQuantity(int quantity);
    void setAvailable(bool status);
    bool updateStock(int quantity);
    void displayInfo() const;
};

#endif 