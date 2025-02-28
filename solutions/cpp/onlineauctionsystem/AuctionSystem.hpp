#ifndef AUCTION_SYSTEM_HPP
#define AUCTION_SYSTEM_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Item.hpp"
#include "Auction.hpp"

class AuctionSystem {
private:
    std::vector<User*> users;
    std::vector<Item*> items;
    std::vector<Auction*> auctions;
    int itemIdCounter;
    int auctionIdCounter;

public:
    AuctionSystem();
    ~AuctionSystem();
    
    User* registerUser(std::string username, std::string email);
    Item* createItem(std::string sellerId, std::string name, std::string description,
                    ItemCategory category, double startingPrice);
    Auction* createAuction(std::string itemId, std::time_t startTime, std::time_t endTime);
    
    bool placeBid(std::string auctionId, std::string bidderId, double amount);
    bool addUserBalance(std::string userId, double amount);
    void startAuction(std::string auctionId);
    void endAuction(std::string auctionId);
    void cancelAuction(std::string auctionId);
    
    std::vector<Auction*> getActiveAuctions() const;
    std::vector<Item*> searchItems(const std::string& query) const;
    
    void displayUserInfo(std::string userId) const;
    void displayItemInfo(std::string itemId) const;
    void displayAuctionInfo(std::string auctionId) const;
    void displayAllAuctions() const;
    
private:
    User* findUser(const std::string& userId) const;
    Item* findItem(const std::string& itemId) const;
    Auction* findAuction(const std::string& auctionId) const;
    std::string generateItemId();
    std::string generateAuctionId();
};

#endif 