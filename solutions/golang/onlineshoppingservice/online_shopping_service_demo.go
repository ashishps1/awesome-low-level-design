package onlineshopping

import (
	"fmt"
)

func Run() {
	shoppingService := GetInstance()

	user1 := NewUser("U001", "John Doe", "john@example.com", "password123")
	user2 := NewUser("U002", "Jane Smith", "jane@example.com", "password456")
	shoppingService.RegisterUser(user1)
	shoppingService.RegisterUser(user2)

	product1 := NewProduct("P001", "Smartphone", "High-end smartphone", 999.99, 10)
	product2 := NewProduct("P002", "Laptop", "Powerful gaming laptop", 1999.99, 5)
	shoppingService.AddProduct(product1)
	shoppingService.AddProduct(product2)

	cart1 := NewShoppingCart()
	cart1.AddItem(product1, 2)
	cart1.AddItem(product2, 1)
	payment1 := &CreditCardPayment{}
	order1, err := shoppingService.PlaceOrder(user1, cart1, payment1)
	if err == nil {
		fmt.Println("Order placed:", order1.ID)
	} else {
		fmt.Println("Failed to place order:", err)
	}

	searchResults := shoppingService.SearchProducts("laptop")
	fmt.Println("Search Results:")
	for _, product := range searchResults {
		fmt.Println(product.Name)
	}

	cart2 := NewShoppingCart()
	cart2.AddItem(searchResults[0], 1)
	payment2 := &CreditCardPayment{}
	order2, err := shoppingService.PlaceOrder(user2, cart2, payment2)
	if err == nil {
		fmt.Println("Order placed:", order2.ID)
	} else {
		fmt.Println("Failed to place order:", err)
	}

	fmt.Println("User 1 Order History:")
	for _, order := range user1.Orders {
		fmt.Printf("Order ID: %s, Total Amount: $%.2f, Status: %v\n", order.ID, order.TotalAmount, order.Status)
	}
}
