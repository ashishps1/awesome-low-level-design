#include "Auction.hpp"
#include <iostream>
#include <iomanip>

Auction::Auction(std::string auctionId, Item* item, std::time_t startTime,
                std::time_t endTime)
    : auctionId(auctionId), item(item), startTime(startTime), endTime(endTime),
      currentPrice(item->getStartingPrice()), status(AuctionStatus::PENDING) {}

std::string Auction::getAuctionId() const { return auctionId; }
Item* Auction::getItem() const { return item; }
std::time_t Auction::getStartTime() const { return startTime; }
std::time_t Auction::getEndTime() const { return endTime; }
double Auction::getCurrentPrice() const { return currentPrice; }
AuctionStatus Auction::getStatus() const { return status; }
std::string Auction::getWinnerId() const { return winnerId; }
const std::vector<Bid>& Auction::getBids() const { return bids; }

bool Auction::placeBid(const std::string& bidderId, double amount) {
    if (status != AuctionStatus::ACTIVE || amount <= currentPrice) {
        return false;
    }
    
    bids.emplace_back(bidderId, amount);
    currentPrice = amount;
    winnerId = bidderId;
    return true;
}

void Auction::start() {
    if (status == AuctionStatus::PENDING) {
        status = AuctionStatus::ACTIVE;
        item->setStatus(ItemStatus::IN_AUCTION);
    }
}

void Auction::end() {
    if (status == AuctionStatus::ACTIVE) {
        status = AuctionStatus::ENDED;
        item->setStatus(ItemStatus::SOLD);
    }
}

void Auction::cancel() {
    status = AuctionStatus::CANCELLED;
    item->setStatus(ItemStatus::AVAILABLE);
    winnerId.clear();
}

bool Auction::isActive() const {
    return status == AuctionStatus::ACTIVE;
}

void Auction::displayInfo() const {
    std::cout << "\nAuction Details:" << std::endl;
    std::cout << "Auction ID: " << auctionId << std::endl;
    item->displayInfo();
    
    std::cout << "Start Time: " << std::ctime(&startTime);
    std::cout << "End Time: " << std::ctime(&endTime);
    std::cout << "Current Price: $" << std::fixed << std::setprecision(2) 
              << currentPrice << std::endl;
    
    std::cout << "Status: ";
    switch (status) {
        case AuctionStatus::PENDING: std::cout << "Pending"; break;
        case AuctionStatus::ACTIVE: std::cout << "Active"; break;
        case AuctionStatus::ENDED: std::cout << "Ended"; break;
        case AuctionStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
    
    if (!bids.empty()) {
        std::cout << "\nBid History:" << std::endl;
        for (const auto& bid : bids) {
            std::cout << "Bidder: " << bid.bidderId 
                      << ", Amount: $" << std::fixed << std::setprecision(2) 
                      << bid.amount 
                      << ", Time: " << std::ctime(&bid.timestamp);
        }
    }
    
    if (!winnerId.empty()) {
        std::cout << "Winner ID: " << winnerId << std::endl;
    }
} 