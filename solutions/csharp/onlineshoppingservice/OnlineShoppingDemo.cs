using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class OnlineShoppingDemo
{
    public static void Main()
    {
        // System Setup (Singleton and Services)
        var system = OnlineShoppingSystem.GetInstance();

        // Create and Add Products to Catalog (Builder Pattern)
        var laptop = new ProductBuilder("Dell XPS 15", 1499.99)
            .WithDescription("A powerful and sleek laptop.")
            .WithCategory(ProductCategory.ELECTRONICS)
            .Build();

        var book = new ProductBuilder("The Pragmatic Programmer", 45.50)
            .WithDescription("A classic book for software developers.")
            .WithCategory(ProductCategory.BOOKS)
            .Build();

        system.AddProduct(laptop, 10); // 10 laptops in stock
        system.AddProduct(book, 50);   // 50 books in stock

        // Register a Customer
        var aliceAddress = new Address("123 Main St", "Anytown", "CA", "12345");
        var alice = system.RegisterCustomer("Alice", "alice@example.com", "password123", aliceAddress);

        // Alice Shops
        Console.WriteLine("--- Alice starts shopping ---");

        // Alice adds a laptop to her cart
        system.AddToCart(alice.GetId(), laptop.GetId(), 1);
        Console.WriteLine("Alice added a laptop to her cart.");

        // Alice decides to gift-wrap the book (Decorator Pattern)
        var giftWrappedBook = new GiftWrapDecorator(book);
        system.AddToCart(alice.GetId(), giftWrappedBook.GetId(), 1);
        Console.WriteLine($"Alice added a gift-wrapped book. Original price: ${book.GetPrice():F2}, New price: ${giftWrappedBook.GetPrice():F2}");

        var aliceCart = system.GetCustomerCart(alice.GetId());
        Console.WriteLine($"Alice's cart total: ${aliceCart.CalculateTotal():F2}");

        // Alice Checks Out
        Console.WriteLine("\n--- Alice proceeds to checkout ---");
        var aliceOrder = system.PlaceOrder(alice.GetId(), new CreditCardPaymentStrategy("1234-5678-9876-5432"));
        if (aliceOrder == null)
        {
            Console.WriteLine("Order placement failed.");
            return;
        }

        Console.WriteLine($"Order #{aliceOrder.GetId()} placed successfully for Alice.");

        // Order State and Notifications (State, Observer Patterns)
        Console.WriteLine("\n--- Order processing starts ---");

        // The warehouse ships the order
        aliceOrder.ShipOrder(); // This will trigger a notification to Alice

        // The delivery service marks the order as delivered
        aliceOrder.DeliverOrder(); // This will also trigger a notification

        // Try to cancel a delivered order (State pattern prevents this)
        aliceOrder.CancelOrder();

        Console.WriteLine("\n--- Out of Stock Scenario ---");
        var bob = system.RegisterCustomer("Bob", "bob@example.com", "pass123", aliceAddress);

        // Bob tries to buy 15 laptops, but only 9 are left (1 was bought by Alice)
        system.AddToCart(bob.GetId(), laptop.GetId(), 15);

        var bobOrder = system.PlaceOrder(bob.GetId(), new UPIPaymentStrategy("testupi@hdfc"));
        if (bobOrder == null)
        {
            Console.WriteLine("Bob's order was correctly prevented due to insufficient stock.");
        }
    }
}