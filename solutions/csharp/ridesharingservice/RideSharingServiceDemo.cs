namespace RideSharingService
{
    public class RideSharingServiceDemo
    {
        public static void Run()
        {
            var rideService = RideService.GetInstance();

            // Create passengers
            var passenger1 = new Passenger(1, "John Doe", "1234567890", new Location(37.7749, -122.4194));
            var passenger2 = new Passenger(2, "Jane Smith", "9876543210", new Location(37.7860, -122.4070));
            rideService.AddPassenger(passenger1);
            rideService.AddPassenger(passenger2);

            // Create drivers
            var driver1 = new Driver(1, "Alice Johnson", "4567890123", "ABC123", new Location(37.7749, -122.4194), DriverStatus.AVAILABLE);
            var driver2 = new Driver(2, "Bob Williams", "7890123456", "XYZ789", new Location(37.7860, -122.4070), DriverStatus.AVAILABLE);
            rideService.AddDriver(driver1);
            rideService.AddDriver(driver2);

            // Passenger 1 requests a ride
            rideService.RequestRide(passenger1, passenger1.Location, new Location(37.7887, -122.4098));

            // Driver 1 accepts the ride
            if (rideService.GetRequestedRides().TryDequeue(out var ride))
            {
                rideService.AcceptRide(driver1, ride);
            }

            // Start the ride
            rideService.StartRide(ride);

            // Complete the ride
            rideService.CompleteRide(ride);

            // Passenger 2 requests a ride
            rideService.RequestRide(passenger2, passenger2.Location, new Location(37.7749, -122.4194));

            // Driver 2 accepts the ride
            if (rideService.GetRequestedRides().TryDequeue(out var ride2))
            {
                rideService.AcceptRide(driver2, ride2);
            }

            // Passenger 2 cancels the ride
            rideService.CancelRide(ride2);
        }
    }
}