using System;
using System.Collections.Generic;

namespace OnlineShopping
{
    public class OnlineShoppingServiceDemo
    {
        public static void Run()
        {
            var shoppingService = OnlineShoppingService.GetInstance();

            // Register users
            var user1 = new User("U001", "John Doe", "john@example.com", "password123");
            var user2 = new User("U002", "Jane Smith", "jane@example.com", "password456");
            shoppingService.RegisterUser(user1);
            shoppingService.RegisterUser(user2);

            // Add products
            var product1 = new Product("P001", "Smartphone", "High-end smartphone", 999.99, 10);
            var product2 = new Product("P002", "Laptop", "Powerful gaming laptop", 1999.99, 5);
            shoppingService.AddProduct(product1);
            shoppingService.AddProduct(product2);

            // User 1 adds products to cart and places an order
            var cart1 = new ShoppingCart();
            cart1.AddItem(product1, 2);
            cart1.AddItem(product2, 1);
            var payment1 = new CreditCardPayment();
            var order1 = shoppingService.PlaceOrder(user1, cart1, payment1);
            Console.WriteLine($"Order placed: {order1.Id}");

            // User 2 searches for products and adds to cart
            var searchResults = shoppingService.SearchProducts("laptop");
            Console.WriteLine("Search Results:");
            foreach (var product in searchResults)
            {
                Console.WriteLine(product.Name);
            }

            var cart2 = new ShoppingCart();
            cart2.AddItem(searchResults[0], 1);
            var payment2 = new CreditCardPayment();
            var order2 = shoppingService.PlaceOrder(user2, cart2, payment2);
            Console.WriteLine($"Order placed: {order2.Id}");

            // User 1 views order history
            var userOrders = user1.Orders;
            Console.WriteLine("User 1 Order History:");
            foreach (var order in userOrders)
            {
                Console.WriteLine($"Order ID: {order.Id}");
                Console.WriteLine($"Total Amount: ${order.TotalAmount}");
                Console.WriteLine($"Status: {order.Status}");
            }
        }
    }
}