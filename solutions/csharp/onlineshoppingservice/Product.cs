namespace OnlineShopping
{
    public class Product
    {
        public string Id { get; }
        public string Name { get; }
        public string Description { get; }
        public double Price { get; }
        private int _quantity;

        public Product(string id, string name, string description, double price, int quantity)
        {
            Id = id;
            Name = name;
            Description = description;
            Price = price;
            _quantity = quantity;
        }

        public void UpdateQuantity(int quantity)
        {
            _quantity += quantity;
        }

        public bool IsAvailable(int quantity)
        {
            return _quantity >= quantity;
        }

        public int Quantity => _quantity;
    }
}