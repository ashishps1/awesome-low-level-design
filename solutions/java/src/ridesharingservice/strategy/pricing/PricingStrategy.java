package ridesharingservice.strategy.pricing;

import ridesharingservice.entities.Location;
import ridesharingservice.enums.RideType;

public interface PricingStrategy {
    double calculateFare(Location pickup, Location dropoff, RideType rideType);
}
