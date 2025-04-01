package onlinestockbrokeragesystem

import "sync"

type Portfolio struct {
	account  *Account
	holdings map[string]int
	mu       sync.RWMutex
}

func NewPortfolio(account *Account) *Portfolio {
	return &Portfolio{
		account:  account,
		holdings: make(map[string]int),
	}
}

func (p *Portfolio) AddStock(stock *Stock, quantity int) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.holdings[stock.Symbol] += quantity
}

func (p *Portfolio) RemoveStock(stock *Stock, quantity int) error {
	p.mu.Lock()
	defer p.mu.Unlock()

	currentQuantity, exists := p.holdings[stock.Symbol]
	if !exists {
		return NewInsufficientStockError("stock not found in portfolio")
	}

	if currentQuantity < quantity {
		return NewInsufficientStockError("insufficient stock quantity in portfolio")
	}

	p.holdings[stock.Symbol] -= quantity
	if p.holdings[stock.Symbol] == 0 {
		delete(p.holdings, stock.Symbol)
	}
	return nil
}

func (p *Portfolio) GetHoldings() map[string]int {
	p.mu.RLock()
	defer p.mu.RUnlock()

	holdings := make(map[string]int)
	for symbol, quantity := range p.holdings {
		holdings[symbol] = quantity
	}
	return holdings
}
