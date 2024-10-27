package onlinestockbrokeragesystem

import (
	"fmt"
	"sync"
)

type StockBroker struct {
	accounts         map[string]*Account
	stocks           map[string]*Stock
	orders           chan Order
	accountIdCounter int
	mu               sync.Mutex
}

var instance *StockBroker
var once sync.Once

func GetStockBrokerInstance() *StockBroker {
	once.Do(func() {
		instance = &StockBroker{
			accounts: make(map[string]*Account),
			stocks:   make(map[string]*Stock),
			orders:   make(chan Order, 100),
		}
		go instance.processOrders()
	})
	return instance
}

func (s *StockBroker) CreateAccount(user *User, initialBalance float64) {
	s.mu.Lock()
	defer s.mu.Unlock()
	accountId := fmt.Sprintf("A%03d", s.accountIdCounter)
	s.accountIdCounter++
	s.accounts[accountId] = NewAccount(accountId, user, initialBalance)
}

func (s *StockBroker) GetAccount(accountId string) *Account {
	return s.accounts[accountId]
}

func (s *StockBroker) AddStock(stock *Stock) {
	s.stocks[stock.symbol] = stock
}

func (s *StockBroker) PlaceOrder(order Order) {
	s.orders <- order
}

func (s *StockBroker) processOrders() {
	for order := range s.orders {
		if err := order.Execute(); err != nil {
			fmt.Println("Order failed:", err)
		}
	}
}
