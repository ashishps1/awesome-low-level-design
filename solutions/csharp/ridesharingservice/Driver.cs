namespace RideSharingService
{
    public class Driver
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Contact { get; set; }
        public string LicensePlate { get; set; }
        public Location Location { get; set; }
        public DriverStatus Status { get; set; }

        public Driver(int id, string name, string contact, string licensePlate, Location location, DriverStatus status)
        {
            Id = id;
            Name = name;
            Contact = contact;
            LicensePlate = licensePlate;
            Location = location;
            Status = status;
        }
    }
}