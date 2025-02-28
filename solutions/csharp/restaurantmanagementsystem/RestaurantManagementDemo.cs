using System;
using System.Collections.Generic;

namespace RestaurantManagementSystem
{
    public class RestaurantManagementDemo
    {
        public static void Run()
        {
            Restaurant restaurant = Restaurant.GetInstance();

            // Add menu items
            restaurant.AddMenuItem(new MenuItem(1, "Burger", "Delicious burger", 9.99, true));
            restaurant.AddMenuItem(new MenuItem(2, "Pizza", "Cheesy pizza", 12.99, true));
            restaurant.AddMenuItem(new MenuItem(3, "Salad", "Fresh salad", 7.99, true));

            // Place an order
            var order = new Order(1, new List<MenuItem>
            {
                new MenuItem(1, "Burger", "Delicious burger", 9.99, true),
                new MenuItem(3, "Salad", "Fresh salad", 7.99, true)
            }, 17.98, OrderStatus.PENDING, DateTime.Now);

            restaurant.PlaceOrder(order);

            // Make a reservation
            var reservation = new Reservation(1, "John Doe", "1234567890", 4, DateTime.Now);
            restaurant.MakeReservation(reservation);

            // Process a payment
            var payment = new Payment(1, 17.98, PaymentMethod.CREDIT_CARD, PaymentStatus.PENDING);
            restaurant.ProcessPayment(payment);

            // Update order status
            restaurant.UpdateOrderStatus(1, OrderStatus.PREPARING);
            restaurant.UpdateOrderStatus(1, OrderStatus.READY);
            restaurant.UpdateOrderStatus(1, OrderStatus.COMPLETED);

            // Add staff
            restaurant.AddStaff(new Staff(1, "Alice", "Manager", "9876543210"));
            restaurant.AddStaff(new Staff(2, "Bob", "Chef", "5432109876"));

            // Get menu
            var menu = restaurant.GetMenu();
            Console.WriteLine("Menu:");
            foreach (var item in menu)
            {
                Console.WriteLine($"{item.Name} - ${item.Price}");
            }
        }
    }
}