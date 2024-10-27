package fooddeliveryservice

import (
	"fmt"
)

func Run() {
	service := GetFoodDeliveryService()

	// Register customers
	customer1 := NewCustomer("C001", "John Doe", "john@example.com", "1234567890")
	customer2 := NewCustomer("C002", "Jane Smith", "jane@example.com", "9876543210")
	service.RegisterCustomer(customer1)
	service.RegisterCustomer(customer2)

	// Create restaurant menus
	restaurant1Menu := []*MenuItem{
		NewMenuItem("M001", "Burger", "Delicious burger", 9.99),
		NewMenuItem("M002", "Pizza", "Cheesy pizza", 12.99),
	}
	restaurant2Menu := []*MenuItem{
		NewMenuItem("M003", "Sushi", "Fresh sushi", 15.99),
		NewMenuItem("M004", "Ramen", "Delicious ramen", 10.99),
	}

	// Register restaurants
	restaurant1 := NewRestaurant("R001", "Restaurant 1", "Address 1", restaurant1Menu)
	restaurant2 := NewRestaurant("R002", "Restaurant 2", "Address 2", restaurant2Menu)
	service.RegisterRestaurant(restaurant1)
	service.RegisterRestaurant(restaurant2)

	// Register delivery agents
	agent1 := NewDeliveryAgent("D001", "Agent 1", "9999999999")
	agent2 := NewDeliveryAgent("D002", "Agent 2", "8888888888")
	service.RegisterDeliveryAgent(agent1)
	service.RegisterDeliveryAgent(agent2)

	// Place orders
	orderItems := []*OrderItem{
		NewOrderItem(restaurant1Menu[0], 2),
		NewOrderItem(restaurant1Menu[1], 1),
	}

	order1, err := service.PlaceOrder(customer1.ID, restaurant1.ID, orderItems)
	if err != nil {
		fmt.Printf("Error placing order: %v\n", err)
		return
	}

	// Update order status
	err = service.UpdateOrderStatus(order1.ID, OrderStatusConfirmed)
	if err != nil {
		fmt.Printf("Error updating order status: %v\n", err)
		return
	}
	fmt.Printf("Order status updated: %s\n", order1.GetStatus())

	// Place and cancel another order
	order2Items := []*OrderItem{
		NewOrderItem(restaurant2Menu[0], 1),
	}
	order2, err := service.PlaceOrder(customer2.ID, restaurant2.ID, order2Items)
	if err != nil {
		fmt.Printf("Error placing order: %v\n", err)
		return
	}

	err = service.CancelOrder(order2.ID)
	if err != nil {
		fmt.Printf("Error cancelling order: %v\n", err)
	}
}
