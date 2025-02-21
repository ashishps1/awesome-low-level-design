#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <string>
#include <map>
#include "Stock.hpp"

class Portfolio {
private:
    std::string userId;
    std::map<std::string, int> holdings;  // symbol -> quantity
    double totalValue;

public:
    Portfolio(std::string userId);
    
    std::string getUserId() const;
    const std::map<std::string, int>& getHoldings() const;
    double getTotalValue() const;
    int getShareQuantity(const std::string& symbol) const;
    
    void addShares(const std::string& symbol, int quantity);
    bool removeShares(const std::string& symbol, int quantity);
    void updateTotalValue(const std::map<std::string, Stock*>& stocks);
    void displayInfo() const;
};

#endif 