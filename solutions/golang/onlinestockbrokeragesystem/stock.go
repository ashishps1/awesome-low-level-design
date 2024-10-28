package onlinestockbrokeragesystem

import "sync"

type Stock struct {
	Symbol string
	Name   string
	price  float64
	mu     sync.RWMutex
}

func NewStock(symbol, name string, price float64) *Stock {
	return &Stock{
		Symbol: symbol,
		Name:   name,
		price:  price,
	}
}

func (s *Stock) UpdatePrice(newPrice float64) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.price = newPrice
}

func (s *Stock) GetPrice() float64 {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.price
}
