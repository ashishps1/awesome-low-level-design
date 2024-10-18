using System.Collections.Generic;
using System.Linq;

namespace OnlineShopping
{
    public class Order
    {
        public string Id { get; }
        public User User { get; }
        public List<OrderItem> Items { get; }
        public double TotalAmount { get; }
        public OrderStatus Status { get; set; }

        public Order(string id, User user, List<OrderItem> items)
        {
            Id = id;
            User = user;
            Items = items;
            TotalAmount = CalculateTotalAmount();
            Status = OrderStatus.Pending;
        }

        private double CalculateTotalAmount()
        {
            return Items.Sum(item => item.Product.Price * item.Quantity);
        }
    }
}