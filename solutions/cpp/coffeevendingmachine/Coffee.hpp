#ifndef COFFEE_HPP
#define COFFEE_HPP

#include <string>
#include "CoffeeType.hpp"

class Coffee {
private:
    CoffeeType type;
    double price;
    std::string description;

public:
    Coffee(CoffeeType type, double price, std::string description);
    
    CoffeeType getType() const;
    double getPrice() const;
    std::string getDescription() const;
};

#endif 