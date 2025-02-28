using System;
using System.Collections.Generic;

namespace RestaurantManagementSystem
{
    public class Order
    {
        public int Id { get; }
        public List<MenuItem> Items { get; }
        public double TotalAmount { get; }
        public OrderStatus Status { get; private set; }
        public DateTime Timestamp { get; }

        public Order(int id, List<MenuItem> items, double totalAmount, OrderStatus status, DateTime timestamp)
        {
            Id = id;
            Items = items;
            TotalAmount = totalAmount;
            Status = status;
            Timestamp = timestamp;
        }

        public void SetStatus(OrderStatus status)
        {
            Status = status;
        }
    }
}