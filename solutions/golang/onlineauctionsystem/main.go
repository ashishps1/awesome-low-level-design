package onlineauctionsystem

import (
	"fmt"
	"time"
)

func Run() {
	auctionSystem := GetInstance()

	// Register users
	user1 := NewUser("1", "John Doe", "john@example.com")
	user2 := NewUser("2", "Jane Smith", "jane@example.com")
	auctionSystem.RegisterUser(user1)
	auctionSystem.RegisterUser(user2)

	// Create auction listings
	listing1 := NewAuctionListing("1", "Item 1", "Description 1", 100.0, 60*time.Second, user1)
	listing2 := NewAuctionListing("2", "Item 2", "Description 2", 50.0, 120*time.Second, user2)
	auctionSystem.CreateAuctionListing(listing1)
	auctionSystem.CreateAuctionListing(listing2)

	// Search auction listings
	searchResults := auctionSystem.SearchAuctionListings("Item")
	fmt.Println("Search Results:")
	for _, listing := range searchResults {
		fmt.Println(listing.ItemName)
	}

	// Place bids
	bid1 := NewBid("1", user2, 150.0)
	bid2 := NewBid("2", user1, 200.0)
	auctionSystem.PlaceBid(listing1.ID, bid1)
	auctionSystem.PlaceBid(listing1.ID, bid2)

	// Wait for a while to see the auction close
	time.Sleep(65 * time.Second)
	fmt.Printf("Auction 1 status: %v\n", listing1.Status)
}
