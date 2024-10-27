package onlinestockbrokeragesystem

type BuyOrder struct {
	*BaseOrder
}

func NewBuyOrder(orderId string, account *Account, stock *Stock, quantity int, price float64) *BuyOrder {
	return &BuyOrder{
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

func (b *BuyOrder) Execute() error {
	totalCost := float64(b.quantity) * b.price
	if b.account.GetBalance() >= totalCost {
		if err := b.account.Withdraw(totalCost); err != nil {
			b.SetStatus(Rejected)
			return err
		}
		b.account.GetPortfolio().AddStock(b.stock, b.quantity)
		b.SetStatus(Executed)
		return nil
	}
	b.SetStatus(Rejected)
	return &InsufficientFundsException{"Insufficient funds to execute the buy order."}
}
