package ridehailingservice.strategy.matching;

import ridehailingservice.entities.Driver;
import ridehailingservice.enums.DriverStatus;
import ridehailingservice.entities.Location;
import ridehailingservice.enums.RideType;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

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
