#ifndef STOCK_HPP
#define STOCK_HPP

#include <string>

class Stock {
private:
    std::string symbol;
    std::string companyName;
    double currentPrice;
    int availableShares;
    bool active;

public:
    Stock(std::string symbol, std::string companyName, double currentPrice, int availableShares);
    
    std::string getSymbol() const;
    std::string getCompanyName() const;
    double getCurrentPrice() const;
    int getAvailableShares() const;
    bool isActive() const;
    
    void setCurrentPrice(double price);
    void updateShares(int quantity);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 