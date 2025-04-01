package onlineauctionsystem

import "time"

type Bid struct {
	ID        string
	Bidder    *User
	Amount    float64
	Timestamp time.Time
}

func NewBid(id string, bidder *User, amount float64) *Bid {
	return &Bid{
		ID:        id,
		Bidder:    bidder,
		Amount:    amount,
		Timestamp: time.Now(),
	}
}
