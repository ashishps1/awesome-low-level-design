package onlinestockbrokeragesystem

type Stock struct {
	symbol string
	name   string
	price  float64
}

func NewStock(symbol, name string, price float64) *Stock {
	return &Stock{symbol: symbol, name: name, price: price}
}

func (s *Stock) UpdatePrice(newPrice float64) {
	s.price = newPrice
}
