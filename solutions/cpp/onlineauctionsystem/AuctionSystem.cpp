#include "AuctionSystem.hpp"
#include <iostream>
#include <algorithm>

AuctionSystem::AuctionSystem() : itemIdCounter(1), auctionIdCounter(1) {}

AuctionSystem::~AuctionSystem() {
    for (auto user : users) delete user;
    for (auto item : items) delete item;
    for (auto auction : auctions) delete auction;
}

User* AuctionSystem::registerUser(std::string username, std::string email) {
    std::string userId = "U" + std::to_string(users.size() + 1);
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

Item* AuctionSystem::createItem(std::string sellerId, std::string name, std::string description,
                              ItemCategory category, double startingPrice) {
    User* seller = findUser(sellerId);
    if (!seller || !seller->isActive()) return nullptr;
    
    Item* item = new Item(generateItemId(), name, description, category,
                         startingPrice, sellerId);
    items.push_back(item);
    seller->addListedItem(item);
    return item;
}

Auction* AuctionSystem::createAuction(std::string itemId, std::time_t startTime,
                                    std::time_t endTime) {
    Item* item = findItem(itemId);
    if (!item || item->getStatus() != ItemStatus::AVAILABLE) return nullptr;
    
    Auction* auction = new Auction(generateAuctionId(), item, startTime, endTime);
    auctions.push_back(auction);
    return auction;
}

bool AuctionSystem::placeBid(std::string auctionId, std::string bidderId, double amount) {
    Auction* auction = findAuction(auctionId);
    User* bidder = findUser(bidderId);
    
    if (!auction || !bidder || !bidder->isActive() || !auction->isActive() ||
        bidder->getBalance() < amount) {
        return false;
    }
    
    if (auction->placeBid(bidderId, amount)) {
        bidder->deductBalance(amount);
        return true;
    }
    return false;
}

bool AuctionSystem::addUserBalance(std::string userId, double amount) {
    User* user = findUser(userId);
    if (user && user->isActive()) {
        user->addBalance(amount);
        return true;
    }
    return false;
}

void AuctionSystem::startAuction(std::string auctionId) {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->start();
}

void AuctionSystem::endAuction(std::string auctionId) {
    Auction* auction = findAuction(auctionId);
    if (auction) {
        auction->end();
        if (!auction->getWinnerId().empty()) {
            User* winner = findUser(auction->getWinnerId());
            if (winner) {
                winner->addPurchasedItem(auction->getItem());
            }
        }
    }
}

void AuctionSystem::cancelAuction(std::string auctionId) {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->cancel();
}

std::vector<Auction*> AuctionSystem::getActiveAuctions() const {
    std::vector<Auction*> activeAuctions;
    for (auto auction : auctions) {
        if (auction->isActive()) {
            activeAuctions.push_back(auction);
        }
    }
    return activeAuctions;
}

std::vector<Item*> AuctionSystem::searchItems(const std::string& query) const {
    std::vector<Item*> results;
    for (auto item : items) {
        if (item->getStatus() == ItemStatus::AVAILABLE &&
            (item->getName().find(query) != std::string::npos ||
             item->getDescription().find(query) != std::string::npos)) {
            results.push_back(item);
        }
    }
    return results;
}

void AuctionSystem::displayUserInfo(std::string userId) const {
    User* user = findUser(userId);
    if (user) user->displayInfo();
}

void AuctionSystem::displayItemInfo(std::string itemId) const {
    Item* item = findItem(itemId);
    if (item) item->displayInfo();
}

void AuctionSystem::displayAuctionInfo(std::string auctionId) const {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->displayInfo();
}

void AuctionSystem::displayAllAuctions() const {
    std::cout << "\nAll Auctions:" << std::endl;
    for (const auto& auction : auctions) {
        auction->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

User* AuctionSystem::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&userId](const User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Item* AuctionSystem::findItem(const std::string& itemId) const {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemId](const Item* item) { return item->getItemId() == itemId; });
    return it != items.end() ? *it : nullptr;
}

Auction* AuctionSystem::findAuction(const std::string& auctionId) const {
    auto it = std::find_if(auctions.begin(), auctions.end(),
        [&auctionId](const Auction* auction) { return auction->getAuctionId() == auctionId; });
    return it != auctions.end() ? *it : nullptr;
}

std::string AuctionSystem::generateItemId() {
    return "I" + std::to_string(itemIdCounter++);
}

std::string AuctionSystem::generateAuctionId() {
    return "A" + std::to_string(auctionIdCounter++);
} 