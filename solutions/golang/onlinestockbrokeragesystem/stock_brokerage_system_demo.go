package onlinestockbrokeragesystem

import "fmt"

func Run() {
	stockBroker := GetStockBrokerInstance()

	user := NewUser("U001", "John Doe", "john@example.com")
	stockBroker.CreateAccount(user, 10000.0)
	account := stockBroker.GetAccount("A001")

	stock1 := NewStock("AAPL", "Apple Inc.", 150.0)
	stock2 := NewStock("GOOGL", "Alphabet Inc.", 2000.0)
	stockBroker.AddStock(stock1)
	stockBroker.AddStock(stock2)

	buyOrder1 := NewBuyOrder("O001", account, stock1, 10, 150.0)
	buyOrder2 := NewBuyOrder("O002", account, stock2, 5, 2000.0)
	stockBroker.PlaceOrder(buyOrder1)
	stockBroker.PlaceOrder(buyOrder2)

	sellOrder1 := NewSellOrder("O003", account, stock1, 5, 160.0)
	stockBroker.PlaceOrder(sellOrder1)

	fmt.Printf("Account Balance: $%.2f\n", account.GetBalance())
	fmt.Printf("Portfolio: %v\n", account.GetPortfolio().GetHoldings())
}
