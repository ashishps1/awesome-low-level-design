# Online Auction System (LLD)

## Problem Statement

Design and implement an Online Auction System that allows users to create auctions, place bids on items, track auction status, and determine winners.

---

## Requirements

- **User Management:** Users can register and participate in auctions.
- **Item Management:** The system manages items that can be auctioned.
- **Auction Creation:** Users can create auctions for items, specifying start and end times.
- **Bidding:** Users can place bids on active auctions.
- **Auction Status Tracking:** The system tracks the status of each auction (e.g., ACTIVE, ENDED).
- **Winner Determination:** The system determines the winning bid and user when an auction ends.
- **Extensibility:** Easy to add new features such as reserve prices, buy-now options, or notifications.

---

## Core Entities

- **AuctionSystem:** Main class that manages users, items, auctions, and bidding.
- **User:** Represents a user who can create auctions and place bids.
- **Item:** Represents an item to be auctioned.
- **Auction:** Represents an auction for an item, including bids, status, and winner.
- **Bid:** Represents a bid placed by a user on an auction.
- **AuctionStatus:** Enum for auction status (ACTIVE, ENDED).

---

## Class Design

## UML Class Diagram

![](../../../../uml-diagrams/class-diagrams/onlineauctionsystem-class-diagram.png)

### 1. AuctionSystem
- **Fields:** List<User> users, List<Item> items, List<Auction> auctions
- **Methods:** registerUser(User), addItem(Item), createAuction(Item, User, Date startTime, Date endTime), placeBid(Auction, User, double amount), endAuction(Auction), getActiveAuctions(), getEndedAuctions(), etc.

### 2. User
- **Fields:** int id, String name

### 3. Item
- **Fields:** int id, String name, String description

### 4. Auction
- **Fields:** int id, Item item, User seller, List<Bid> bids, AuctionStatus status, User winner, Date startTime, Date endTime
- **Methods:** addBid(Bid), endAuction(), getHighestBid(), getWinner()

### 5. Bid
- **Fields:** int id, User bidder, double amount, Date bidTime

### 6. AuctionStatus (enum)
- Values: ACTIVE, ENDED

---

## Example Usage

```java
AuctionSystem system = new AuctionSystem();
User alice = new User(1, "Alice");
User bob = new User(2, "Bob");
system.registerUser(alice);
system.registerUser(bob);

Item painting = new Item(1, "Painting", "Beautiful landscape painting");
system.addItem(painting);

Auction auction = system.createAuction(painting, alice, new Date(), new Date(System.currentTimeMillis() + 3600000));
system.placeBid(auction, bob, 100.0);
system.placeBid(auction, alice, 120.0);

system.endAuction(auction);
User winner = auction.getWinner();
System.out.println("Winner: " + (winner != null ? winner.getName() : "No winner"));
```

---

## Demo

See `AuctionSystemDemo.java` for a sample usage and simulation of the online auction system.

---

## Extending the Framework

- **Add reserve prices:** Only sell if the highest bid meets the minimum price.
- **Add buy-now options:** Allow instant purchase at a set price.
- **Add notifications:** Notify users of auction events or outbids.

---