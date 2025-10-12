package ridehailingservice.strategy.pricing;

import ridehailingservice.entities.Location;
import ridehailingservice.enums.RideType;

public interface PricingStrategy {
    double calculateFare(Location pickup, Location dropoff, RideType rideType);
}
