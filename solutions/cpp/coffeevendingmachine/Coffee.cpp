#include "Coffee.hpp"

Coffee::Coffee(CoffeeType type, double price, std::string description)
    : type(type), price(price), description(description) {}

CoffeeType Coffee::getType() const { return type; }
double Coffee::getPrice() const { return price; }
std::string Coffee::getDescription() const { return description; } 