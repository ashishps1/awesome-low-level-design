package onlinestockbrokeragesystem

type Portfolio struct {
	holdings map[string]int
}

func NewPortfolio() *Portfolio {
	return &Portfolio{holdings: make(map[string]int)}
}

func (p *Portfolio) AddStock(stock *Stock, quantity int) {
	p.holdings[stock.symbol] += quantity
}

func (p *Portfolio) RemoveStock(stock *Stock, quantity int) error {
	currentQuantity, exists := p.holdings[stock.symbol]
	if !exists || currentQuantity < quantity {
		return NewInsufficientStockException("Insufficient stock quantity in the portfolio.")
	}
	p.holdings[stock.symbol] -= quantity
	if p.holdings[stock.symbol] == 0 {
		delete(p.holdings, stock.symbol)
	}
	return nil
}

func (p *Portfolio) GetHoldings() map[string]int {
	return p.holdings
}
