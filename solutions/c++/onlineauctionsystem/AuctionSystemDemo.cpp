#include "AuctionSystem.hpp"
#include <iostream>
#include <ctime>

int main() {
    AuctionSystem system;
    
    // Register users
    User* seller = system.registerUser("john_seller", "john@email.com");
    User* bidder1 = system.registerUser("alice_bidder", "alice@email.com");
    User* bidder2 = system.registerUser("bob_bidder", "bob@email.com");
    
    // Add balance to bidders
    system.addUserBalance(bidder1->getUserId(), 1000.0);
    system.addUserBalance(bidder2->getUserId(), 1500.0);
    
    std::cout << "Initial user balances:" << std::endl;
    system.displayUserInfo(bidder1->getUserId());
    system.displayUserInfo(bidder2->getUserId());
    
    // Create items
    Item* phone = system.createItem(seller->getUserId(), "Smartphone", 
                                  "Latest model smartphone", 
                                  ItemCategory::ELECTRONICS, 500.0);
    Item* watch = system.createItem(seller->getUserId(), "Luxury Watch",
                                  "Vintage luxury timepiece",
                                  ItemCategory::FASHION, 1000.0);
    
    if (phone && watch) {
        std::cout << "\nCreated items:" << std::endl;
        system.displayItemInfo(phone->getItemId());
        system.displayItemInfo(watch->getItemId());
        
        // Create auctions
        std::time_t now = std::time(nullptr);
        std::time_t oneHourLater = now + 3600;
        
        Auction* phoneAuction = system.createAuction(phone->getItemId(), now, oneHourLater);
        Auction* watchAuction = system.createAuction(watch->getItemId(), now, oneHourLater);
        
        if (phoneAuction && watchAuction) {
            // Start auctions
            system.startAuction(phoneAuction->getAuctionId());
            system.startAuction(watchAuction->getAuctionId());
            
            std::cout << "\nActive auctions:" << std::endl;
            system.displayAllAuctions();
            
            // Place bids
            std::cout << "\nPlacing bids..." << std::endl;
            if (system.placeBid(phoneAuction->getAuctionId(), 
                              bidder1->getUserId(), 600.0)) {
                std::cout << "Bid placed successfully by " 
                         << bidder1->getUsername() << std::endl;
            }
            
            if (system.placeBid(phoneAuction->getAuctionId(), 
                              bidder2->getUserId(), 700.0)) {
                std::cout << "Bid placed successfully by " 
                         << bidder2->getUsername() << std::endl;
            }
            
            if (system.placeBid(watchAuction->getAuctionId(), 
                              bidder2->getUserId(), 1200.0)) {
                std::cout << "Bid placed successfully by " 
                         << bidder2->getUsername() << std::endl;
            }
            
            // Display auction status
            std::cout << "\nCurrent auction status:" << std::endl;
            system.displayAuctionInfo(phoneAuction->getAuctionId());
            system.displayAuctionInfo(watchAuction->getAuctionId());
            
            // End auctions
            std::cout << "\nEnding auctions..." << std::endl;
            system.endAuction(phoneAuction->getAuctionId());
            system.endAuction(watchAuction->getAuctionId());
            
            // Display final results
            std::cout << "\nFinal auction results:" << std::endl;
            system.displayAuctionInfo(phoneAuction->getAuctionId());
            system.displayAuctionInfo(watchAuction->getAuctionId());
            
            // Display updated user balances
            std::cout << "\nFinal user balances:" << std::endl;
            system.displayUserInfo(bidder1->getUserId());
            system.displayUserInfo(bidder2->getUserId());
        }
    }
    
    return 0;
} 