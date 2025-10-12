using System;
using System.Collections.Generic;
using System.Linq;

public class RideSharingServiceDemo
{
    public static void Main()
    {
        // 1. Setup the system using singleton instance
        var service = RideSharingService.Instance;
        service.SetDriverMatchingStrategy(new NearestDriverMatchingStrategy());
        service.SetPricingStrategy(new VehicleBasedPricingStrategy());

        // 2. Register riders and drivers
        var alice = service.RegisterRider("Alice", "123-456-7890");

        var bobVehicle = new Vehicle("KA01-1234", "Toyota Prius", RideType.SEDAN);
        var bob = service.RegisterDriver("Bob", "243-987-2860", bobVehicle, new Location(1.0, 1.0));

        var charlieVehicle = new Vehicle("KA02-5678", "Honda CRV", RideType.SUV);
        var charlie = service.RegisterDriver("Charlie", "313-486-2691", charlieVehicle, new Location(2.0, 2.0));

        var davidVehicle = new Vehicle("KA03-9012", "Honda CRV", RideType.SEDAN);
        var david = service.RegisterDriver("David", "613-586-3241", davidVehicle, new Location(1.2, 1.2));

        // 3. Drivers go online
        bob.SetStatus(DriverStatus.ONLINE);
        charlie.SetStatus(DriverStatus.ONLINE);
        david.SetStatus(DriverStatus.ONLINE);

        // David is online but will be too far for the first request
        david.SetCurrentLocation(new Location(10.0, 10.0));

        // 4. Alice requests a ride
        var pickupLocation = new Location(0.0, 0.0);
        var dropoffLocation = new Location(5.0, 5.0);

        // Rider wants a SEDAN
        var trip1 = service.RequestRide(alice.Id, pickupLocation, dropoffLocation, RideType.SEDAN);

        if (trip1 != null)
        {
            // 5. One of the nearby drivers accepts the ride
            service.AcceptRide(bob.Id, trip1.Id);

            // 6. The trip progresses
            service.StartTrip(trip1.Id);
            service.EndTrip(trip1.Id);
        }

        Console.WriteLine("\n--- Checking Trip History ---");
        Console.WriteLine($"Alice's trip history: {alice.TripHistory.Count} trips");
        Console.WriteLine($"Bob's trip history: {bob.TripHistory.Count} trips");

        // --- Second ride request ---
        Console.WriteLine("\n=============================================");
        var harry = service.RegisterRider("Harry", "167-342-7834");

        // Harry requests an SUV
        var trip2 = service.RequestRide(harry.Id,
            new Location(2.5, 2.5),
            new Location(8.0, 8.0),
            RideType.SUV);

        if (trip2 != null)
        {
            // Only Charlie is available for an SUV ride
            service.AcceptRide(charlie.Id, trip2.Id);
            service.StartTrip(trip2.Id);
            service.EndTrip(trip2.Id);
        }
    }
}