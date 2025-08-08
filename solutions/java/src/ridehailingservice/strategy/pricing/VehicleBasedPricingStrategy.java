package ridehailingservice.strategy.pricing;

import ridehailingservice.entities.Location;
import ridehailingservice.enums.RideType;

import java.util.Map;

public class VehicleBasedPricingStrategy implements PricingStrategy {
    private static final double BASE_FARE = 2.50;
    private static final Map<RideType, Double> RATE_PER_KM = Map.of(
            RideType.SEDAN, 1.50,
            RideType.SUV, 2.00,
            RideType.AUTO, 1.00
    );

    @Override
    public double calculateFare(Location pickup, Location dropoff, RideType rideType) {
        return BASE_FARE + RATE_PER_KM.get(rideType) * pickup.distanceTo(dropoff);
    }
}
