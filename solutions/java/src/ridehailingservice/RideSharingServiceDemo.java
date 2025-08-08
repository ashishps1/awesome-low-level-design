package ridehailingservice;

import ridehailingservice.enums.DriverStatus;
import ridehailingservice.enums.RideType;
import ridehailingservice.entities.Driver;
import ridehailingservice.entities.Location;
import ridehailingservice.entities.Trip;
import ridehailingservice.entities.Vehicle;
import ridehailingservice.observer.Rider;
import ridehailingservice.strategy.matching.NearestDriverMatchingStrategy;
import ridehailingservice.strategy.pricing.VehicleBasedPricingStrategy;

public class RideSharingServiceDemo {
    public static void main(String[] args) {
        // 1. Setup the system using singleton instance
        RideSharingService service = RideSharingService.getInstance();
        service.setDriverMatchingStrategy(new NearestDriverMatchingStrategy());
        service.setPricingStrategy(new VehicleBasedPricingStrategy());

        // 2. Register riders and drivers
        Rider alice = service.registerRider("Alice", "123-456-7890");

        Driver bob = service.registerDriver("Bob",
                "243-987-2860",
                new Vehicle("KA01-1234", "Toyota Prius", RideType.SEDAN),
                new Location(1.0, 1.0));

        Driver charlie = service.registerDriver("Charlie",
                "313-486-2691",
                new Vehicle("KA02-5678", "Honda CRV", RideType.SUV),
                new Location(2.0, 2.0));

        Driver david = service.registerDriver("David",
                "613-586-3241",
                new Vehicle("KA03-9012", "Honda CRV", RideType.SEDAN),
                new Location(1.2, 1.2));

        // 3. Drivers go online
        bob.setStatus(DriverStatus.ONLINE);
        charlie.setStatus(DriverStatus.ONLINE);
        david.setStatus(DriverStatus.ONLINE);

        // David is online but will be too far for the first request
        david.setCurrentLocation(new Location(10.0, 10.0));

        // 4. Alice requests a ride
        Location pickupLocation = new Location(0.0, 0.0);
        Location dropoffLocation = new Location(5.0, 5.0);

        // Rider wants a SEDAN
        Trip trip1 = service.requestRide(alice.getId(), pickupLocation, dropoffLocation, RideType.SEDAN);

        if (trip1 != null) {
            // 5. One of the nearby drivers accepts the ride
            // In this case, Bob (1.0, 1.0) is closer than David (10.0, 10.0 is too far).
            // Charlie is ignored because he drives an SUV.
            service.acceptRide(bob.getId(), trip1.getId());

            // 6. The trip progresses
            service.startTrip(trip1.getId());
            service.endTrip(trip1.getId());
        }

        System.out.println("\n--- Checking Trip History ---");
        System.out.println("Alice's trip history: " + alice.getTripHistory());
        System.out.println("Bob's trip history: " + bob.getTripHistory());

        // --- Second ride request ---
        System.out.println("\n=============================================");
        Rider harry = service.registerRider("Harry", "167-342-7834");

        // Harry requests an SUV
        Trip trip2 = service.requestRide(harry.getId(),
                new Location(2.5, 2.5),
                new Location(8.0, 8.0),
                RideType.SUV);

        if(trip2 != null) {
            // Only Charlie is available for an SUV ride
            service.acceptRide(charlie.getId(), trip2.getId());
            service.startTrip(trip2.getId());
            service.endTrip(trip2.getId());
        }
    }
}
