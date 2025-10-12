package ridehailingservice.strategy.matching;

import ridehailingservice.entities.Driver;
import ridehailingservice.entities.Location;
import ridehailingservice.enums.RideType;

import java.util.List;

public interface DriverMatchingStrategy {
    List<Driver> findDrivers(List<Driver> allDrivers, Location pickupLocation, RideType rideType);
}
