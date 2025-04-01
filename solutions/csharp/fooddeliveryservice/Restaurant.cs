using System.Collections.Generic;

namespace FoodDeliveryService
{
    public class Restaurant
    {
        public string Id { get; }
        public string Name { get; }
        public string Address { get; }
        public List<MenuItem> Menu { get; }

        public Restaurant(string id, string name, string address, List<MenuItem> menu)
        {
            Id = id;
            Name = name;
            Address = address;
            Menu = menu;
        }

        public void AddMenuItem(MenuItem item)
        {
            Menu.Add(item);
        }

        public void RemoveMenuItem(MenuItem item)
        {
            Menu.Remove(item);
        }
    }
}