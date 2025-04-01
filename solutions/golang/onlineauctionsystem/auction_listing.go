package onlineauctionsystem

import (
	"sync"
	"time"
)

type AuctionListing struct {
	ID                   string
	ItemName             string
	Description          string
	StartingPrice        float64
	Duration             time.Duration
	Seller               *User
	Status               AuctionStatus
	CurrentHighestBid    float64
	CurrentHighestBidder *User
	Bids                 []*Bid
	mu                   sync.Mutex
	observers            []chan struct{} // Simple channel-based observer pattern
}

func NewAuctionListing(id, itemName, description string, startingPrice float64, duration time.Duration, seller *User) *AuctionListing {
	return &AuctionListing{
		ID:                id,
		ItemName:          itemName,
		Description:       description,
		StartingPrice:     startingPrice,
		Duration:          duration,
		Seller:            seller,
		Status:            StatusActive,
		CurrentHighestBid: startingPrice,
		Bids:              make([]*Bid, 0),
		observers:         make([]chan struct{}, 0),
	}
}

func (a *AuctionListing) PlaceBid(bid *Bid) bool {
	a.mu.Lock()
	defer a.mu.Unlock()

	if a.Status == StatusActive && bid.Amount > a.CurrentHighestBid {
		a.CurrentHighestBid = bid.Amount
		a.CurrentHighestBidder = bid.Bidder
		a.Bids = append(a.Bids, bid)
		a.notifyObservers()
		return true
	}
	return false
}

func (a *AuctionListing) CloseAuction() {
	a.mu.Lock()
	defer a.mu.Unlock()

	if a.Status == StatusActive {
		a.Status = StatusClosed
		a.notifyObservers()
	}
}

func (a *AuctionListing) notifyObservers() {
	for _, observer := range a.observers {
		select {
		case observer <- struct{}{}: // Non-blocking send
		default:
		}
	}
}
