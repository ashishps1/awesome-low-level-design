package onlinestockbrokeragesystem

type BuyOrder struct {
	BaseOrder
}

func NewBuyOrder(orderID string, account *Account, stock *Stock, quantity int, price float64) *BuyOrder {
	return &BuyOrder{
		BaseOrder: BaseOrder{
			OrderID:  orderID,
			Account:  account,
			Stock:    stock,
			Quantity: quantity,
			Price:    price,
			Status:   OrderStatusPending,
		},
	}
}

func (o *BuyOrder) Execute() error {
	totalCost := float64(o.Quantity) * o.Price

	if err := o.Account.Withdraw(totalCost); err != nil {
		o.Status = OrderStatusRejected
		return err
	}

	o.Account.Portfolio.AddStock(o.Stock, o.Quantity)
	o.Status = OrderStatusExecuted
	return nil
}
