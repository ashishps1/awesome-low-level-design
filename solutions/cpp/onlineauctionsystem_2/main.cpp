// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Item;
class User;
class Bid;
class Auction;
class AuctionSystem;

// ===== Item.hpp =====
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
    string itemId;
    string name;
    string description;
    ItemCategory category;
    double startingPrice;
    ItemStatus status;
    string sellerId;

public:
    Item(string itemId, string name, string description,
         ItemCategory category, double startingPrice, string sellerId);
    
    string getItemId() const;
    string getName() const;
    string getDescription() const;
    ItemCategory getCategory() const;
    double getStartingPrice() const;
    ItemStatus getStatus() const;
    string getSellerId() const;
    
    void setStatus(ItemStatus status);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    double balance;
    vector<Item*> listedItems;
    vector<Item*> purchasedItems;
    bool active;

public:
    User(string userId, string username, string email);
    ~User();
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    double getBalance() const;
    bool isActive() const;
    const vector<Item*>& getListedItems() const;
    const vector<Item*>& getPurchasedItems() const;
    
    void addBalance(double amount);
    bool deductBalance(double amount);
    void addListedItem(Item* item);
    void addPurchasedItem(Item* item);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Auction.hpp =====
struct Bid {
    string bidderId;
    double amount;
    time_t timestamp;
    
    Bid(string bidderId, double amount)
        : bidderId(bidderId), amount(amount), timestamp(time(nullptr)) {}
};

enum class AuctionStatus {
    PENDING,
    ACTIVE,
    ENDED,
    CANCELLED
};

class Auction {
private:
    string auctionId;
    Item* item;
    time_t startTime;
    time_t endTime;
    double currentPrice;
    vector<Bid> bids;
    AuctionStatus status;
    string winnerId;

public:
    Auction(string auctionId, Item* item, time_t startTime,
           time_t endTime);
    
    string getAuctionId() const;
    Item* getItem() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
    double getCurrentPrice() const;
    AuctionStatus getStatus() const;
    string getWinnerId() const;
    const vector<Bid>& getBids() const;
    
    bool placeBid(const string& bidderId, double amount);
    void start();
    void end();
    void cancel();
    bool isActive() const;
    void displayInfo() const;
};

// ===== AuctionSystem.hpp =====
class AuctionSystem {
private:
    vector<User*> users;
    vector<Item*> items;
    vector<Auction*> auctions;
    int itemIdCounter;
    int auctionIdCounter;

public:
    AuctionSystem();
    ~AuctionSystem();
    
    User* registerUser(string username, string email);
    Item* createItem(string sellerId, string name, string description,
                    ItemCategory category, double startingPrice);
    Auction* createAuction(string itemId, time_t startTime, time_t endTime);
    
    bool placeBid(string auctionId, string bidderId, double amount);
    bool addUserBalance(string userId, double amount);
    void startAuction(string auctionId);
    void endAuction(string auctionId);
    void cancelAuction(string auctionId);
    
    vector<Auction*> getActiveAuctions() const;
    vector<Item*> searchItems(const string& query) const;
    
    void displayUserInfo(string userId) const;
    void displayItemInfo(string itemId) const;
    void displayAuctionInfo(string auctionId) const;
    void displayAllAuctions() const;
    
private:
    User* findUser(const string& userId) const;
    Item* findItem(const string& itemId) const;
    Auction* findAuction(const string& auctionId) const;
    string generateItemId();
    string generateAuctionId();
};

// ===== Auction.cpp =====
Auction::Auction(string auctionId, Item* item, time_t startTime,
                time_t endTime)
    : auctionId(auctionId), item(item), startTime(startTime), endTime(endTime),
      currentPrice(item->getStartingPrice()), status(AuctionStatus::PENDING) {}

string Auction::getAuctionId() const { return auctionId; }
Item* Auction::getItem() const { return item; }
time_t Auction::getStartTime() const { return startTime; }
time_t Auction::getEndTime() const { return endTime; }
double Auction::getCurrentPrice() const { return currentPrice; }
AuctionStatus Auction::getStatus() const { return status; }
string Auction::getWinnerId() const { return winnerId; }
const vector<Bid>& Auction::getBids() const { return bids; }

bool Auction::placeBid(const string& bidderId, double amount) {
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
    cout << "\nAuction Details:" << endl;
    cout << "Auction ID: " << auctionId << endl;
    item->displayInfo();
    
    cout << "Start Time: " << ctime(&startTime);
    cout << "End Time: " << ctime(&endTime);
    cout << "Current Price: $" << fixed << setprecision(2) 
              << currentPrice << endl;
    
    cout << "Status: ";
    switch (status) {
        case AuctionStatus::PENDING: cout << "Pending"; break;
        case AuctionStatus::ACTIVE: cout << "Active"; break;
        case AuctionStatus::ENDED: cout << "Ended"; break;
        case AuctionStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
    
    if (!bids.empty()) {
        cout << "\nBid History:" << endl;
        for (const auto& bid : bids) {
            cout << "Bidder: " << bid.bidderId 
                      << ", Amount: $" << fixed << setprecision(2) 
                      << bid.amount 
                      << ", Time: " << ctime(&bid.timestamp);
        }
    }
    
    if (!winnerId.empty()) {
        cout << "Winner ID: " << winnerId << endl;
    }
} 

// ===== AuctionSystem.cpp =====
AuctionSystem::AuctionSystem() : itemIdCounter(1), auctionIdCounter(1) {}

AuctionSystem::~AuctionSystem() {
    for (auto user : users) delete user;
    for (auto item : items) delete item;
    for (auto auction : auctions) delete auction;
}

User* AuctionSystem::registerUser(string username, string email) {
    string userId = "U" + to_string(users.size() + 1);
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

Item* AuctionSystem::createItem(string sellerId, string name, string description,
                              ItemCategory category, double startingPrice) {
    User* seller = findUser(sellerId);
    if (!seller || !seller->isActive()) return nullptr;
    
    Item* item = new Item(generateItemId(), name, description, category,
                         startingPrice, sellerId);
    items.push_back(item);
    seller->addListedItem(item);
    return item;
}

Auction* AuctionSystem::createAuction(string itemId, time_t startTime,
                                    time_t endTime) {
    Item* item = findItem(itemId);
    if (!item || item->getStatus() != ItemStatus::AVAILABLE) return nullptr;
    
    Auction* auction = new Auction(generateAuctionId(), item, startTime, endTime);
    auctions.push_back(auction);
    return auction;
}

bool AuctionSystem::placeBid(string auctionId, string bidderId, double amount) {
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

bool AuctionSystem::addUserBalance(string userId, double amount) {
    User* user = findUser(userId);
    if (user && user->isActive()) {
        user->addBalance(amount);
        return true;
    }
    return false;
}

void AuctionSystem::startAuction(string auctionId) {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->start();
}

void AuctionSystem::endAuction(string auctionId) {
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

void AuctionSystem::cancelAuction(string auctionId) {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->cancel();
}

vector<Auction*> AuctionSystem::getActiveAuctions() const {
    vector<Auction*> activeAuctions;
    for (auto auction : auctions) {
        if (auction->isActive()) {
            activeAuctions.push_back(auction);
        }
    }
    return activeAuctions;
}

vector<Item*> AuctionSystem::searchItems(const string& query) const {
    vector<Item*> results;
    for (auto item : items) {
        if (item->getStatus() == ItemStatus::AVAILABLE &&
            (item->getName().find(query) != string::npos ||
             item->getDescription().find(query) != string::npos)) {
            results.push_back(item);
        }
    }
    return results;
}

void AuctionSystem::displayUserInfo(string userId) const {
    User* user = findUser(userId);
    if (user) user->displayInfo();
}

void AuctionSystem::displayItemInfo(string itemId) const {
    Item* item = findItem(itemId);
    if (item) item->displayInfo();
}

void AuctionSystem::displayAuctionInfo(string auctionId) const {
    Auction* auction = findAuction(auctionId);
    if (auction) auction->displayInfo();
}

void AuctionSystem::displayAllAuctions() const {
    cout << "\nAll Auctions:" << endl;
    for (const auto& auction : auctions) {
        auction->displayInfo();
        cout << "------------------------" << endl;
    }
}

User* AuctionSystem::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [&userId](const User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Item* AuctionSystem::findItem(const string& itemId) const {
    auto it = find_if(items.begin(), items.end(),
        [&itemId](const Item* item) { return item->getItemId() == itemId; });
    return it != items.end() ? *it : nullptr;
}

Auction* AuctionSystem::findAuction(const string& auctionId) const {
    auto it = find_if(auctions.begin(), auctions.end(),
        [&auctionId](const Auction* auction) { return auction->getAuctionId() == auctionId; });
    return it != auctions.end() ? *it : nullptr;
}

string AuctionSystem::generateItemId() {
    return "I" + to_string(itemIdCounter++);
}

string AuctionSystem::generateAuctionId() {
    return "A" + to_string(auctionIdCounter++);
} 

// ===== Item.cpp =====
Item::Item(string itemId, string name, string description,
           ItemCategory category, double startingPrice, string sellerId)
    : itemId(itemId), name(name), description(description), category(category),
      startingPrice(startingPrice), sellerId(sellerId), status(ItemStatus::AVAILABLE) {}

string Item::getItemId() const { return itemId; }
string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
ItemCategory Item::getCategory() const { return category; }
double Item::getStartingPrice() const { return startingPrice; }
ItemStatus Item::getStatus() const { return status; }
string Item::getSellerId() const { return sellerId; }

void Item::setStatus(ItemStatus status) {
    this->status = status;
}

void Item::displayInfo() const {
    cout << "Item: " << name << " (ID: " << itemId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Category: ";
    switch (category) {
        case ItemCategory::ELECTRONICS: cout << "Electronics"; break;
        case ItemCategory::FASHION: cout << "Fashion"; break;
        case ItemCategory::HOME: cout << "Home"; break;
        case ItemCategory::SPORTS: cout << "Sports"; break;
        case ItemCategory::BOOKS: cout << "Books"; break;
        case ItemCategory::COLLECTIBLES: cout << "Collectibles"; break;
        case ItemCategory::OTHER: cout << "Other"; break;
    }
    cout << endl;
    
    cout << "Starting Price: $" << fixed << setprecision(2) 
              << startingPrice << endl;
    cout << "Status: ";
    switch (status) {
        case ItemStatus::AVAILABLE: cout << "Available"; break;
        case ItemStatus::IN_AUCTION: cout << "In Auction"; break;
        case ItemStatus::SOLD: cout << "Sold"; break;
        case ItemStatus::WITHDRAWN: cout << "Withdrawn"; break;
    }
    cout << endl;
    cout << "Seller ID: " << sellerId << endl;
} 

// ===== User.cpp =====
User::User(string userId, string username, string email)
    : userId(userId), username(username), email(email), balance(0.0), active(true) {}

User::~User() {
    // Note: Items are managed by the auction system
    listedItems.clear();
    purchasedItems.clear();
}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
double User::getBalance() const { return balance; }
bool User::isActive() const { return active; }
const vector<Item*>& User::getListedItems() const { return listedItems; }
const vector<Item*>& User::getPurchasedItems() const { return purchasedItems; }

void User::addBalance(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool User::deductBalance(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void User::addListedItem(Item* item) {
    listedItems.push_back(item);
}

void User::addPurchasedItem(Item* item) {
    purchasedItems.push_back(item);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Listed Items: " << listedItems.size() << endl;
    cout << "Purchased Items: " << purchasedItems.size() << endl;
} 

// ===== AuctionSystemDemo.cpp =====
int main() {
    AuctionSystem system;
    
    // Register users
    User* seller = system.registerUser("john_seller", "john@email.com");
    User* bidder1 = system.registerUser("alice_bidder", "alice@email.com");
    User* bidder2 = system.registerUser("bob_bidder", "bob@email.com");
    
    // Add balance to bidders
    system.addUserBalance(bidder1->getUserId(), 1000.0);
    system.addUserBalance(bidder2->getUserId(), 1500.0);
    
    cout << "Initial user balances:" << endl;
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
        cout << "\nCreated items:" << endl;
        system.displayItemInfo(phone->getItemId());
        system.displayItemInfo(watch->getItemId());
        
        // Create auctions
        time_t now = time(nullptr);
        time_t oneHourLater = now + 3600;
        
        Auction* phoneAuction = system.createAuction(phone->getItemId(), now, oneHourLater);
        Auction* watchAuction = system.createAuction(watch->getItemId(), now, oneHourLater);
        
        if (phoneAuction && watchAuction) {
            // Start auctions
            system.startAuction(phoneAuction->getAuctionId());
            system.startAuction(watchAuction->getAuctionId());
            
            cout << "\nActive auctions:" << endl;
            system.displayAllAuctions();
            
            // Place bids
            cout << "\nPlacing bids..." << endl;
            if (system.placeBid(phoneAuction->getAuctionId(), 
                              bidder1->getUserId(), 600.0)) {
                cout << "Bid placed successfully by " 
                         << bidder1->getUsername() << endl;
            }
            
            if (system.placeBid(phoneAuction->getAuctionId(), 
                              bidder2->getUserId(), 700.0)) {
                cout << "Bid placed successfully by " 
                         << bidder2->getUsername() << endl;
            }
            
            if (system.placeBid(watchAuction->getAuctionId(), 
                              bidder2->getUserId(), 1200.0)) {
                cout << "Bid placed successfully by " 
                         << bidder2->getUsername() << endl;
            }
            
            // Display auction status
            cout << "\nCurrent auction status:" << endl;
            system.displayAuctionInfo(phoneAuction->getAuctionId());
            system.displayAuctionInfo(watchAuction->getAuctionId());
            
            // End auctions
            cout << "\nEnding auctions..." << endl;
            system.endAuction(phoneAuction->getAuctionId());
            system.endAuction(watchAuction->getAuctionId());
            
            // Display final results
            cout << "\nFinal auction results:" << endl;
            system.displayAuctionInfo(phoneAuction->getAuctionId());
            system.displayAuctionInfo(watchAuction->getAuctionId());
            
            // Display updated user balances
            cout << "\nFinal user balances:" << endl;
            system.displayUserInfo(bidder1->getUserId());
            system.displayUserInfo(bidder2->getUserId());
        }
    }
    
    return 0;
} 

