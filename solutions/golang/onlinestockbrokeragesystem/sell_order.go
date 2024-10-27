package onlinestockbrokeragesystem

type SellOrder struct {
	*BaseOrder
}

func NewSellOrder(orderId string, account *Account, stock *Stock, quantity int, price float64) *SellOrder {
	return &SellOrder{
		BaseOrder: &BaseOrder{
			orderId:  orderId,
			account:  account,
			stock:    stock,
			quantity: quantity,
			price:    price,
			status:   Pending,
		},
	}
}

func (s *SellOrder) Execute() error {
	if err := s.account.GetPortfolio().RemoveStock(s.stock, s.quantity); err != nil {
		s.SetStatus(Rejected)
		return err
	}
	totalProceeds := float64(s.quantity) * s.price
	s.account.Deposit(totalProceeds)
	s.SetStatus(Executed)
	return nil
}
