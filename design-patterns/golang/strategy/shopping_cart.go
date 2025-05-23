package strategy

import "fmt"

// ShoppingCart is the context that uses a payment strategy
type ShoppingCart struct {
	amount   float64
	strategy PaymentStrategy
}

func NewShoppingCart(amount float64) *ShoppingCart {
	return &ShoppingCart{amount: amount}
}

func (c *ShoppingCart) SetPaymentStrategy(strategy PaymentStrategy) {
	c.strategy = strategy
}

func (c *ShoppingCart) Checkout() {
	if c.strategy == nil {
		fmt.Println("No payment strategy selected.")
		return
	}
	result := c.strategy.Pay(c.amount)
	fmt.Println(result)
}
