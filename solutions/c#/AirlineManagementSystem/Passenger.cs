namespace AirlineManagementSystem
{
    public class Passenger
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string Phone { get; }

        public Passenger(string id, string name, string email, string phone)
        {
            Id = id;
            Name = name;
            Email = email;
            Phone = phone;
        }
    }
}