#include "Item.hpp"
#include <iostream>
#include <iomanip>

Item::Item(std::string itemId, std::string name, std::string description,
           ItemCategory category, double startingPrice, std::string sellerId)
    : itemId(itemId), name(name), description(description), category(category),
      startingPrice(startingPrice), sellerId(sellerId), status(ItemStatus::AVAILABLE) {}

std::string Item::getItemId() const { return itemId; }
std::string Item::getName() const { return name; }
std::string Item::getDescription() const { return description; }
ItemCategory Item::getCategory() const { return category; }
double Item::getStartingPrice() const { return startingPrice; }
ItemStatus Item::getStatus() const { return status; }
std::string Item::getSellerId() const { return sellerId; }

void Item::setStatus(ItemStatus status) {
    this->status = status;
}

void Item::displayInfo() const {
    std::cout << "Item: " << name << " (ID: " << itemId << ")" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Category: ";
    switch (category) {
        case ItemCategory::ELECTRONICS: std::cout << "Electronics"; break;
        case ItemCategory::FASHION: std::cout << "Fashion"; break;
        case ItemCategory::HOME: std::cout << "Home"; break;
        case ItemCategory::SPORTS: std::cout << "Sports"; break;
        case ItemCategory::BOOKS: std::cout << "Books"; break;
        case ItemCategory::COLLECTIBLES: std::cout << "Collectibles"; break;
        case ItemCategory::OTHER: std::cout << "Other"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Starting Price: $" << std::fixed << std::setprecision(2) 
              << startingPrice << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case ItemStatus::AVAILABLE: std::cout << "Available"; break;
        case ItemStatus::IN_AUCTION: std::cout << "In Auction"; break;
        case ItemStatus::SOLD: std::cout << "Sold"; break;
        case ItemStatus::WITHDRAWN: std::cout << "Withdrawn"; break;
    }
    std::cout << std::endl;
    std::cout << "Seller ID: " << sellerId << std::endl;
} 