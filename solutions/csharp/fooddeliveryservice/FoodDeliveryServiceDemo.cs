using System;
using System.Collections.Generic;

namespace FoodDeliveryService
{
    public class FoodDeliveryServiceDemo
    {
        public static void Run()
        {
            var deliveryService = FoodDeliveryService.Instance;

            // Register customers
            var customer1 = new Customer("C001", "John Doe", "john@example.com", "1234567890");
            var customer2 = new Customer("C002", "Jane Smith", "jane@example.com", "9876543210");
            deliveryService.RegisterCustomer(customer1);
            deliveryService.RegisterCustomer(customer2);

            // Register restaurants
            var restaurant1Menu = new List<MenuItem>
            {
                new MenuItem("M001", "Burger", "Delicious burger", 9.99),
                new MenuItem("M002", "Pizza", "Cheesy pizza", 12.99)
            };
            var restaurant1 = new Restaurant("R001", "Restaurant 1", "Address 1", restaurant1Menu);
            deliveryService.RegisterRestaurant(restaurant1);

            var restaurant2Menu = new List<MenuItem>
            {
                new MenuItem("M003", "Sushi", "Fresh sushi", 15.99),
                new MenuItem("M004", "Ramen", "Delicious ramen", 10.99)
            };
            var restaurant2 = new Restaurant("R002", "Restaurant 2", "Address 2", restaurant2Menu);
            deliveryService.RegisterRestaurant(restaurant2);

            // Register delivery agents
            var agent1 = new DeliveryAgent("D001", "Agent 1", "9999999999");
            var agent2 = new DeliveryAgent("D002", "Agent 2", "8888888888");
            deliveryService.RegisterDeliveryAgent(agent1);
            deliveryService.RegisterDeliveryAgent(agent2);

            // Place an order
            var orderItems = new List<OrderItem>
            {
                new OrderItem(restaurant1Menu[0], 2),
                new OrderItem(restaurant1Menu[1], 1)
            };
            var order = deliveryService.PlaceOrder(customer1.Id, restaurant1.Id, orderItems);

            // Update order status
            deliveryService.UpdateOrderStatus(order.Id, OrderStatus.CONFIRMED);
            Console.WriteLine($"Order status updated: {order.Status}");

            // Cancel an order
            var order2 = deliveryService.PlaceOrder(customer2.Id, restaurant2.Id, new List<OrderItem> { new OrderItem(restaurant2Menu[0], 1) });
            deliveryService.CancelOrder(order2.Id);
        }
    }
}