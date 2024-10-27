package restaurantmanagementsystem

import (
	"fmt"
	"time"
)

func Run() {
	restaurant := GetRestaurantInstance()

	// Add menu items
	restaurant.AddMenuItem(NewMenuItem(1, "Burger", "Delicious burger", 9.99, true))
	restaurant.AddMenuItem(NewMenuItem(2, "Pizza", "Cheesy pizza", 12.99, true))
	restaurant.AddMenuItem(NewMenuItem(3, "Salad", "Fresh salad", 7.99, true))

	// Place an order
	order := NewOrder(1, []MenuItem{
		*NewMenuItem(1, "Burger", "Delicious burger", 9.99, true),
		*NewMenuItem(3, "Salad", "Fresh salad", 7.99, true),
	}, 17.98, OrderPending)
	restaurant.PlaceOrder(order)

	// Make a reservation
	reservation := NewReservation(1, "John Doe", "1234567890", 4, time.Now())
	restaurant.MakeReservation(reservation)

	// Process a payment
	payment := NewPayment(1, 17.98, CreditCard, PaymentPending)
	restaurant.ProcessPayment(payment)

	// Update order status
	restaurant.UpdateOrderStatus(1, OrderPreparing)
	restaurant.UpdateOrderStatus(1, OrderReady)
	restaurant.UpdateOrderStatus(1, OrderCompleted)

	// Add staff
	restaurant.AddStaff(NewStaff(1, "Alice", "Manager", "9876543210"))
	restaurant.AddStaff(NewStaff(2, "Bob", "Chef", "5432109876"))

	// Get menu
	fmt.Println("Menu:")
	for _, item := range restaurant.GetMenu() {
		fmt.Printf("%s - $%.2f\n", item.Name, item.Price)
	}
}
