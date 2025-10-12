from ride_sharing_service import RideSharingService
from driver_matching_strategy import NearestDriverMatchingStrategy
from pricing_strategy import VehicleBasedPricingStrategy
from enums import DriverStatus, RideType
from location import Location
from vehicle import Vehicle

class RideSharingServiceDemo:
    @staticmethod
    def main():
        # 1. Setup the system using singleton instance
        service = RideSharingService.get_instance()
        service.set_driver_matching_strategy(NearestDriverMatchingStrategy())
        service.set_pricing_strategy(VehicleBasedPricingStrategy())
        
        # 2. Register riders and drivers
        alice = service.register_rider("Alice", "123-456-7890")
        
        bob = service.register_driver("Bob",
                                    "243-987-2860",
                                    Vehicle("KA01-1234", "Toyota Prius", RideType.SEDAN),
                                    Location(1.0, 1.0))
        
        charlie = service.register_driver("Charlie",
                                        "313-486-2691",
                                        Vehicle("KA02-5678", "Honda CRV", RideType.SUV),
                                        Location(2.0, 2.0))
        
        david = service.register_driver("David",
                                      "613-586-3241",
                                      Vehicle("KA03-9012", "Honda CRV", RideType.SEDAN),
                                      Location(1.2, 1.2))
        
        # 3. Drivers go online
        bob.set_status(DriverStatus.ONLINE)
        charlie.set_status(DriverStatus.ONLINE)
        david.set_status(DriverStatus.ONLINE)
        
        # David is online but will be too far for the first request
        david.set_current_location(Location(10.0, 10.0))
        
        # 4. Alice requests a ride
        pickup_location = Location(0.0, 0.0)
        dropoff_location = Location(5.0, 5.0)
        
        # Rider wants a SEDAN
        trip1 = service.request_ride(alice.get_id(), pickup_location, dropoff_location, RideType.SEDAN)
        
        if trip1 is not None:
            # 5. One of the nearby drivers accepts the ride
            # In this case, Bob (1.0, 1.0) is closer than David (10.0, 10.0 is too far).
            # Charlie is ignored because he drives an SUV.
            service.accept_ride(bob.get_id(), trip1.get_id())
            
            # 6. The trip progresses
            service.start_trip(trip1.get_id())
            service.end_trip(trip1.get_id())
        
        print("\n--- Checking Trip History ---")
        print(f"Alice's trip history: {alice.get_trip_history()}")
        print(f"Bob's trip history: {bob.get_trip_history()}")
        
        # --- Second ride request ---
        print("\n=============================================")
        harry = service.register_rider("Harry", "167-342-7834")
        
        # Harry requests an SUV
        trip2 = service.request_ride(harry.get_id(),
                                    Location(2.5, 2.5),
                                    Location(8.0, 8.0),
                                    RideType.SUV)
        
        if trip2 is not None:
            # Only Charlie is available for an SUV ride
            service.accept_ride(charlie.get_id(), trip2.get_id())
            service.start_trip(trip2.get_id())
            service.end_trip(trip2.get_id())

if __name__ == "__main__":
    RideSharingServiceDemo.main()