namespace RestaurantManagementSystem
{
    public class MenuItem
    {
        public int Id { get; }
        public string Name { get; }
        public string Description { get; }
        public double Price { get; }
        public bool Available { get; }

        public MenuItem(int id, string name, string description, double price, bool available)
        {
            Id = id;
            Name = name;
            Description = description;
            Price = price;
            Available = available;
        }
    }
}