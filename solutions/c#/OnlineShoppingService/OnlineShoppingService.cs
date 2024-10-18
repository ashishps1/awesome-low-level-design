using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace OnlineShopping
{
    public class OnlineShoppingService
    {
        private static OnlineShoppingService _instance;
        private readonly ConcurrentDictionary<string, User> _users;
        private readonly ConcurrentDictionary<string, Product> _products;
        private readonly ConcurrentDictionary<string, Order> _orders;

        private OnlineShoppingService()
        {
            _users = new ConcurrentDictionary<string, User>();
            _products = new ConcurrentDictionary<string, Product>();
            _orders = new ConcurrentDictionary<string, Order>();
        }

        public static OnlineShoppingService GetInstance()
        {
            if (_instance == null)
            {
                _instance = new OnlineShoppingService();
            }
            return _instance;
        }

        public void RegisterUser(User user)
        {
            _users[user.Id] = user;
        }

        public User GetUser(string userId)
        {
            _users.TryGetValue(userId, out var user);
            return user;
        }

        public void AddProduct(Product product)
        {
            _products[product.Id] = product;
        }

        public Product GetProduct(string productId)
        {
            _products.TryGetValue(productId, out var product);
            return product;
        }

        public List<Product> SearchProducts(string keyword)
        {
            return _products.Values
                .Where(p => p.Name.Contains(keyword, StringComparison.OrdinalIgnoreCase))
                .ToList();
        }

        public Order PlaceOrder(User user, ShoppingCart cart, Payment payment)
        {
            var orderItems = new List<OrderItem>();

            foreach (var item in cart.GetItems())
            {
                var product = item.Product;
                var quantity = item.Quantity;
                if (product.IsAvailable(quantity))
                {
                    product.UpdateQuantity(-quantity);
                    orderItems.Add(item);
                }
            }

            if (!orderItems.Any())
            {
                throw new InvalidOperationException("No available products in the cart.");
            }

            var orderId = GenerateOrderId();
            var order = new Order(orderId, user, orderItems);
            _orders[orderId] = order;
            user.AddOrder(order);
            cart.Clear();

            if (payment.ProcessPayment(order.TotalAmount))
            {
                order.Status = OrderStatus.Processing;
            }
            else
            {
                order.Status = OrderStatus.Cancelled;
                // Revert product quantities
                foreach (var item in orderItems)
                {
                    item.Product.UpdateQuantity(item.Quantity);
                }
            }

            return order;
        }

        public Order GetOrder(string orderId)
        {
            _orders.TryGetValue(orderId, out var order);
            return order;
        }

        private string GenerateOrderId()
        {
            return $"ORDER{Guid.NewGuid().ToString().Substring(0, 8).ToUpper()}";
        }
    }
}