namespace FoodDeliveryService
{
    public class MenuItem
    {
        public string Id { get; }
        public string Name { get; }
        public string Description { get; }
        public double Price { get; }
        public bool Available { get; private set; }

        public MenuItem(string id, string name, string description, double price)
        {
            Id = id;
            Name = name;
            Description = description;
            Price = price;
            Available = true;
        }

        public void SetAvailable(bool available)
        {
            Available = available;
        }
    }
}