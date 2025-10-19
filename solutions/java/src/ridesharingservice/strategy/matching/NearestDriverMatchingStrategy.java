package ridesharingservice.strategy.matching;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

import ridesharingservice.entities.Driver;
import ridesharingservice.entities.Location;
import ridesharingservice.enums.DriverStatus;
import ridesharingservice.enums.RideType;

public class NearestDriverMatchingStrategy implements DriverMatchingStrategy {
    private static final double MAX_DISTANCE_KM = 5.0; // Max distance to consider a driver "nearby"

    @Override
    public List<Driver> findDrivers(List<Driver> allDrivers, Location pickupLocation, RideType rideType) {
        System.out.println("Finding nearest drivers for ride type: " + rideType);
        return allDrivers.stream()
                .filter(driver -> driver.getStatus() == DriverStatus.ONLINE)
                .filter(driver -> driver.getVehicle().getType() == rideType)
                .filter(driver -> pickupLocation.distanceTo(driver.getCurrentLocation()) <= MAX_DISTANCE_KM)
                .sorted(Comparator.comparingDouble(driver -> pickupLocation.distanceTo(driver.getCurrentLocation())))
                .collect(Collectors.toList());
    }
}
