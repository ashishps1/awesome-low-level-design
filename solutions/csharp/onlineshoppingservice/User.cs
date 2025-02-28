using System.Collections.Generic;

namespace OnlineShopping
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string Password { get; }
        public List<Order> Orders { get; }

        public User(string id, string name, string email, string password)
        {
            Id = id;
            Name = name;
            Email = email;
            Password = password;
            Orders = new List<Order>();
        }

        public void AddOrder(Order order)
        {
            Orders.Add(order);
        }
    }
}