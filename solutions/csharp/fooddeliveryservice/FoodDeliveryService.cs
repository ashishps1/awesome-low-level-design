using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace FoodDeliveryService
{
    public class FoodDeliveryService
    {
        private static FoodDeliveryService _instance;
        private readonly ConcurrentDictionary<string, Customer> _customers;
        private readonly ConcurrentDictionary<string, Restaurant> _restaurants;
        private readonly ConcurrentDictionary<string, Order> _orders;
        private readonly ConcurrentDictionary<string, DeliveryAgent> _deliveryAgents;

        private FoodDeliveryService()
        {
            _customers = new ConcurrentDictionary<string, Customer>();
            _restaurants = new ConcurrentDictionary<string, Restaurant>();
            _orders = new ConcurrentDictionary<string, Order>();
            _deliveryAgents = new ConcurrentDictionary<string, DeliveryAgent>();
        }

        public static FoodDeliveryService Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new FoodDeliveryService();
                }
                return _instance;
            }
        }

        public void RegisterCustomer(Customer customer)
        {
            _customers[customer.Id] = customer;
        }

        public void RegisterRestaurant(Restaurant restaurant)
        {
            _restaurants[restaurant.Id] = restaurant;
        }

        public void RegisterDeliveryAgent(DeliveryAgent agent)
        {
            _deliveryAgents[agent.Id] = agent;
        }

        public List<Restaurant> GetAvailableRestaurants()
        {
            return new List<Restaurant>(_restaurants.Values);
        }

        public List<MenuItem> GetRestaurantMenu(string restaurantId)
        {
            if (_restaurants.TryGetValue(restaurantId, out var restaurant))
            {
                return restaurant.Menu;
            }
            return new List<MenuItem>();
        }

        public Order PlaceOrder(string customerId, string restaurantId, List<OrderItem> items)
        {
            if (_customers.TryGetValue(customerId, out var customer) && _restaurants.TryGetValue(restaurantId, out var restaurant))
            {
                var order = new Order(GenerateOrderId(), customer, restaurant);
                foreach (var item in items)
                {
                    order.AddItem(item);
                }
                _orders[order.Id] = order;
                NotifyRestaurant(order);
                Console.WriteLine($"Order placed: {order.Id}");
                return order;
            }
            return null;
        }

        public void UpdateOrderStatus(string orderId, OrderStatus status)
        {
            if (_orders.TryGetValue(orderId, out var order))
            {
                order.SetStatus(status);
                NotifyCustomer(order);
                if (status == OrderStatus.CONFIRMED)
                {
                    AssignDeliveryAgent(order);
                }
            }
        }

        public void CancelOrder(string orderId)
        {
            if (_orders.TryGetValue(orderId, out var order) && order.Status == OrderStatus.PENDING)
            {
                order.SetStatus(OrderStatus.CANCELLED);
                NotifyCustomer(order);
                NotifyRestaurant(order);
                Console.WriteLine($"Order cancelled: {order.Id}");
            }
        }

        private void NotifyCustomer(Order order)
        {
            // Send notification to the customer about the order status update
        }

        private void NotifyRestaurant(Order order)
        {
            // Send notification to the restaurant about the new order or order status update
        }

        private void AssignDeliveryAgent(Order order)
        {
            foreach (var agent in _deliveryAgents.Values)
            {
                if (agent.Available)
                {
                    agent.SetAvailable(false);
                    order.AssignDeliveryAgent(agent);
                    NotifyDeliveryAgent(order);
                    break;
                }
            }
        }

        private void NotifyDeliveryAgent(Order order)
        {
            // Send notification to the delivery agent about the assigned order
        }

        private string GenerateOrderId()
        {
            return "ORD" + Guid.NewGuid().ToString().Substring(0, 8).ToUpper();
        }
    }
}