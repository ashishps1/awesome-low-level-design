package ridehailingservice.strategy.pricing;

import ridehailingservice.entities.Location;
import ridehailingservice.enums.RideType;

public class FlatRatePricingStrategy implements PricingStrategy {
    private static final double BASE_FARE = 5.0;
    private static final double FLAT_RATE = 1.5;

    @Override
    public double calculateFare(Location pickup, Location dropoff, RideType rideType) {
        double distance = pickup.distanceTo(dropoff);
        return BASE_FARE + distance * FLAT_RATE;
    }
}