#ifndef AUCTION_HPP
#define AUCTION_HPP

#include <string>
#include <vector>
#include <ctime>
#include "Item.hpp"
#include "User.hpp"

struct Bid {
    std::string bidderId;
    double amount;
    std::time_t timestamp;
    
    Bid(std::string bidderId, double amount)
        : bidderId(bidderId), amount(amount), timestamp(std::time(nullptr)) {}
};

enum class AuctionStatus {
    PENDING,
    ACTIVE,
    ENDED,
    CANCELLED
};

class Auction {
private:
    std::string auctionId;
    Item* item;
    std::time_t startTime;
    std::time_t endTime;
    double currentPrice;
    std::vector<Bid> bids;
    AuctionStatus status;
    std::string winnerId;

public:
    Auction(std::string auctionId, Item* item, std::time_t startTime,
           std::time_t endTime);
    
    std::string getAuctionId() const;
    Item* getItem() const;
    std::time_t getStartTime() const;
    std::time_t getEndTime() const;
    double getCurrentPrice() const;
    AuctionStatus getStatus() const;
    std::string getWinnerId() const;
    const std::vector<Bid>& getBids() const;
    
    bool placeBid(const std::string& bidderId, double amount);
    void start();
    void end();
    void cancel();
    bool isActive() const;
    void displayInfo() const;
};

#endif 