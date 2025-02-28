namespace RideSharingService
{
    public class Passenger
    {
        public int Id { get; }
        public string Name { get; }
        public string Contact { get; }
        public Location Location { get; }

        public Passenger(int id, string name, string contact, Location location)
        {
            Id = id;
            Name = name;
            Contact = contact;
            Location = location;
        }
    }
}