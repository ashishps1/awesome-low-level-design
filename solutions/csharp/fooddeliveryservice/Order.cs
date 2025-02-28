using System.Collections.Generic;

namespace FoodDeliveryService
{
    public class Order
    {
        public string Id { get; }
        public Customer Customer { get; }
        public Restaurant Restaurant { get; }
        public List<OrderItem> Items { get; }
        public OrderStatus Status { get; private set; }
        public DeliveryAgent DeliveryAgent { get; private set; }

        public Order(string id, Customer customer, Restaurant restaurant)
        {
            Id = id;
            Customer = customer;
            Restaurant = restaurant;
            Items = new List<OrderItem>();
            Status = OrderStatus.PENDING;
        }

        public void AddItem(OrderItem item)
        {
            Items.Add(item);
        }

        public void SetStatus(OrderStatus status)
        {
            Status = status;
        }

        public void AssignDeliveryAgent(DeliveryAgent agent)
        {
            DeliveryAgent = agent;
        }
    }
}