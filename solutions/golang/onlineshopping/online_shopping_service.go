package onlineshopping

import (
	"errors"
	"fmt"
	"strings"
)

type OnlineShoppingService struct {
	Users    map[string]*User
	Products map[string]*Product
	Orders   map[string]*Order
}

var instance *OnlineShoppingService

func GetInstance() *OnlineShoppingService {
	if instance == nil {
		instance = &OnlineShoppingService{
			Users:    make(map[string]*User),
			Products: make(map[string]*Product),
			Orders:   make(map[string]*Order),
		}
	}
	return instance
}

func (s *OnlineShoppingService) RegisterUser(user *User) {
	s.Users[user.ID] = user
}

func (s *OnlineShoppingService) AddProduct(product *Product) {
	s.Products[product.ID] = product
}

func (s *OnlineShoppingService) SearchProducts(keyword string) []*Product {
	var results []*Product
	for _, product := range s.Products {
		if strings.Contains(strings.ToLower(product.Name), strings.ToLower(keyword)) {
			results = append(results, product)
		}
	}
	return results
}

func (s *OnlineShoppingService) PlaceOrder(user *User, cart *ShoppingCart, paymentMethod Payment) (*Order, error) {
	var orderItems []OrderItem
	for _, item := range cart.GetItems() {
		product := item.Product
		quantity := item.Quantity
		if product.IsAvailable(quantity) {
			product.UpdateQuantity(-quantity)
			orderItems = append(orderItems, item)
		}
	}

	if len(orderItems) == 0 {
		return nil, errors.New("no available products in the cart")
	}

	order := NewOrder(fmt.Sprintf("ORDER-%s", user.ID), user, orderItems)
	s.Orders[order.ID] = order
	user.AddOrder(*order)
	cart.Clear()

	if paymentMethod.ProcessPayment(order.TotalAmount) {
		order.SetStatus(Processing)
	} else {
		order.SetStatus(Cancelled)
		for _, item := range orderItems {
			item.Product.UpdateQuantity(item.Quantity)
		}
	}

	return order, nil
}
