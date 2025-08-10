using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class FoodDeliveryServiceDemo
{
    public static void Main(string[] args)
    {
        // 1. Setup the system
        FoodDeliveryService service = FoodDeliveryService.GetInstance();
        service.SetAssignmentStrategy(new NearestAvailableAgentStrategy());

        // 2. Define Addresses
        Address aliceAddress = new Address("123 Maple St", "Springfield", "12345", 40.7128, -74.0060);
        Address pizzaAddress = new Address("456 Oak Ave", "Springfield", "12345", 40.7138, -74.0070);
        Address burgerAddress = new Address("789 Pine Ln", "Springfield", "12345", 40.7108, -74.0050);
        Address tacoAddress = new Address("101 Elm Ct", "Shelbyville", "54321", 41.7528, -75.0160);

        // 3. Register entities
        Customer alice = service.RegisterCustomer("Alice", "123-4567-890", aliceAddress);
        Restaurant pizzaPalace = service.RegisterRestaurant("Pizza Palace", pizzaAddress);
        Restaurant burgerBarn = service.RegisterRestaurant("Burger Barn", burgerAddress);
        Restaurant tacoTown = service.RegisterRestaurant("Taco Town", tacoAddress);
        service.RegisterDeliveryAgent("Bob", "321-4567-880", new Address("1 B", "Springfield", "12345", 40.71, -74.00));

        // 4. Setup menus
        pizzaPalace.AddToMenu(new MenuItem("P001", "Margherita Pizza", 12.99));
        pizzaPalace.AddToMenu(new MenuItem("P002", "Veggie Pizza", 11.99));
        burgerBarn.AddToMenu(new MenuItem("B001", "Classic Burger", 8.99));
        tacoTown.AddToMenu(new MenuItem("T001", "Crunchy Taco", 3.50));

        // 5. Demonstrate Search Functionality
        Console.WriteLine("\n--- 1. Searching for Restaurants ---");

        // (A) Search by City
        Console.WriteLine("\n(A) Restaurants in 'Springfield':");
        List<IRestaurantSearchStrategy> citySearch = new List<IRestaurantSearchStrategy> { new SearchByCityStrategy("Springfield") };
        List<Restaurant> springfieldRestaurants = service.SearchRestaurants(citySearch);
        foreach (var r in springfieldRestaurants)
        {
            Console.WriteLine($"  - {r.GetName()}");
        }

        // (B) Search for restaurants near Alice
        Console.WriteLine("\n(B) Restaurants near Alice (within 0.01 distance units):");
        List<IRestaurantSearchStrategy> proximitySearch = new List<IRestaurantSearchStrategy> { new SearchByProximityStrategy(aliceAddress, 0.01) };
        List<Restaurant> nearbyRestaurants = service.SearchRestaurants(proximitySearch);
        foreach (var r in nearbyRestaurants)
        {
            Console.WriteLine($"  - {r.GetName()} (Distance: {aliceAddress.DistanceTo(r.GetAddress()):F4})");
        }

        // (C) Search for restaurants that serve 'Pizza'
        Console.WriteLine("\n(C) Restaurants that serve 'Pizza':");
        List<IRestaurantSearchStrategy> menuSearch = new List<IRestaurantSearchStrategy> { new SearchByMenuKeywordStrategy("Pizza") };
        List<Restaurant> pizzaRestaurants = service.SearchRestaurants(menuSearch);
        foreach (var r in pizzaRestaurants)
        {
            Console.WriteLine($"  - {r.GetName()}");
        }

        // (D) Combined Search: Find restaurants near Alice that serve 'Burger'
        Console.WriteLine("\n(D) Burger joints near Alice:");
        List<IRestaurantSearchStrategy> combinedSearch = new List<IRestaurantSearchStrategy>
        {
            new SearchByProximityStrategy(aliceAddress, 0.01),
            new SearchByMenuKeywordStrategy("Burger")
        };
        List<Restaurant> burgerJointsNearAlice = service.SearchRestaurants(combinedSearch);
        foreach (var r in burgerJointsNearAlice)
        {
            Console.WriteLine($"  - {r.GetName()}");
        }

        // 6. Demonstrate Browsing a Menu
        Console.WriteLine("\n--- 2. Browsing a Menu ---");
        Console.WriteLine("\nMenu for 'Pizza Palace':");
        Menu pizzaMenu = service.GetRestaurantMenu(pizzaPalace.GetId());
        foreach (var item in pizzaMenu.GetItems().Values)
        {
            Console.WriteLine($"  - {item.GetName()}: ${item.GetPrice():F2}");
        }

        // 7. Alice places an order from a searched restaurant
        Console.WriteLine("\n--- 3. Placing an Order ---");
        if (pizzaRestaurants.Count > 0)
        {
            Restaurant chosenRestaurant = pizzaRestaurants[0];
            MenuItem chosenItem = chosenRestaurant.GetMenu().GetItem("P001");

            Console.WriteLine($"\nAlice is ordering '{chosenItem.GetName()}' from '{chosenRestaurant.GetName()}'.");
            var order = service.PlaceOrder(alice.GetId(), chosenRestaurant.GetId(), new List<OrderItem> { new OrderItem(chosenItem, 1) });

            Console.WriteLine("\n--- Restaurant starts preparing the order ---");
            service.UpdateOrderStatus(order.GetId(), OrderStatus.PREPARING);

            Console.WriteLine("\n--- Order is ready for pickup ---");
            Console.WriteLine("System will now find the nearest available delivery agent...");
            service.UpdateOrderStatus(order.GetId(), OrderStatus.READY_FOR_PICKUP);

            Console.WriteLine("\n--- Agent delivers the order ---");
            service.UpdateOrderStatus(order.GetId(), OrderStatus.DELIVERED);
        }
    }
}