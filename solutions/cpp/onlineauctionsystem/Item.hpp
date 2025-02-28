#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

enum class ItemCategory {
    ELECTRONICS,
    FASHION,
    HOME,
    SPORTS,
    BOOKS,
    COLLECTIBLES,
    OTHER
};

enum class ItemStatus {
    AVAILABLE,
    IN_AUCTION,
    SOLD,
    WITHDRAWN
};

class Item {
private:
    std::string itemId;
    std::string name;
    std::string description;
    ItemCategory category;
    double startingPrice;
    ItemStatus status;
    std::string sellerId;

public:
    Item(std::string itemId, std::string name, std::string description,
         ItemCategory category, double startingPrice, std::string sellerId);
    
    std::string getItemId() const;
    std::string getName() const;
    std::string getDescription() const;
    ItemCategory getCategory() const;
    double getStartingPrice() const;
    ItemStatus getStatus() const;
    std::string getSellerId() const;
    
    void setStatus(ItemStatus status);
    void displayInfo() const;
};

#endif 