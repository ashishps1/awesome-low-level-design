namespace RideSharingService
{
    public class Ride
    {
        public int Id { get; }
        public Passenger Passenger { get; }
        public Driver Driver { get; private set; }
        public Location Source { get; }
        public Location Destination { get; }
        public RideStatus Status { get; private set; }
        public double Fare { get; private set; }

        public Ride(int id, Passenger passenger, Driver driver, Location source, Location destination, RideStatus status, double fare)
        {
            Id = id;
            Passenger = passenger;
            Driver = driver;
            Source = source;
            Destination = destination;
            Status = status;
            Fare = fare;
        }

        public void SetDriver(Driver driver)
        {
            Driver = driver;
        }

        public void SetStatus(RideStatus status)
        {
            Status = status;
        }

        public void SetFare(double fare)
        {
            Fare = fare;
        }
    }
}