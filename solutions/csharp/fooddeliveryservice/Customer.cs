namespace FoodDeliveryService
{
    public class Customer
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string Phone { get; }

        public Customer(string id, string name, string email, string phone)
        {
            Id = id;
            Name = name;
            Email = email;
            Phone = phone;
        }
    }
}