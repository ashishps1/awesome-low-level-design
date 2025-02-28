namespace RestaurantManagementSystem
{
    public class Staff
    {
        public int Id { get; }
        public string Name { get; }
        public string Role { get; }
        public string ContactNumber { get; }

        public Staff(int id, string name, string role, string contactNumber)
        {
            Id = id;
            Name = name;
            Role = role;
            ContactNumber = contactNumber;
        }
    }
}