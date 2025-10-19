package ridesharingservice.strategy.matching;

import java.util.List;

import ridesharingservice.entities.Driver;
import ridesharingservice.entities.Location;
import ridesharingservice.enums.RideType;

public interface DriverMatchingStrategy {
    List<Driver> findDrivers(List<Driver> allDrivers, Location pickupLocation, RideType rideType);
}
