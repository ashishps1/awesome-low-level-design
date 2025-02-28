using System;
using System.Collections.Generic;
using System.Collections.Concurrent;

namespace RestaurantManagementSystem
{
    public class Restaurant
    {
        private static Restaurant instance;
        private readonly List<MenuItem> menu;
        private readonly ConcurrentDictionary<int, Order> orders;
        private readonly List<Reservation> reservations;
        private readonly ConcurrentDictionary<int, Payment> payments;
        private readonly List<Staff> staff;

        private Restaurant()
        {
            menu = new List<MenuItem>();
            orders = new ConcurrentDictionary<int, Order>();
            reservations = new List<Reservation>();
            payments = new ConcurrentDictionary<int, Payment>();
            staff = new List<Staff>();
        }

        public static Restaurant GetInstance()
        {
            if (instance == null)
            {
                instance = new Restaurant();
            }
            return instance;
        }

        public void AddMenuItem(MenuItem item)
        {
            menu.Add(item);
        }

        public void RemoveMenuItem(MenuItem item)
        {
            menu.Remove(item);
        }

        public List<MenuItem> GetMenu()
        {
            return new List<MenuItem>(menu);
        }

        public void PlaceOrder(Order order)
        {
            orders[order.Id] = order;
            NotifyKitchen(order);
        }

        public void UpdateOrderStatus(int orderId, OrderStatus status)
        {
            if (orders.TryGetValue(orderId, out var order))
            {
                order.SetStatus(status);
                NotifyStaff(order);
            }
        }

        public void MakeReservation(Reservation reservation)
        {
            reservations.Add(reservation);
        }

        public void CancelReservation(Reservation reservation)
        {
            reservations.Remove(reservation);
        }

        public void ProcessPayment(Payment payment)
        {
            payments[payment.Id] = payment;
            // Payment processing logic
        }

        public void AddStaff(Staff staffMember)
        {
            staff.Add(staffMember);
        }

        public void RemoveStaff(Staff staffMember)
        {
            staff.Remove(staffMember);
        }

        private void NotifyKitchen(Order order)
        {
            // Notify kitchen staff to prepare the order
        }

        private void NotifyStaff(Order order)
        {
            // Notify relevant staff about the order status update
        }
    }
}