# Designing a Ride-Sharing Service Like Uber

This article explores the object-oriented design and implementation of a Ride-Sharing Service similar to Uber using Java. 

We focus on the various aspects of ride-sharing, including user and driver management, ride booking, and fare calculation.

## System Requirements

The Ride-Sharing Service should:

1. **User and Driver Account Management**: Handle the registration and profiles of users and drivers.
2. **Ride Booking**: Enable users to book rides and drivers to accept them.
3. **Fare Calculation**: Compute fares based on distance and other factors.
4. **Ride History Management**: Keep a record of past rides for users and drivers.

## Core Use Cases

1. **Registering and Managing User and Driver Accounts**
2. **Booking and Managing Rides**
3. **Calculating and Processing Fares**
4. **Maintaining Ride History**

## Key Classes:
- `RideSharingService`: Manages the overall system.
- `User`: Represents a service user.
- `Driver`: Represents a driver.
- `Ride`: Manages ride details.
- `FareCalculator`: Calculates ride fares.

## Java Implementation

### User Class

Manages user account information.

```java
public class User {
    private String userId;
    private String name;
    private String phone;

    public User(String userId, String name, String phone) {
        this.userId = userId;
        this.name = name;
        this.phone = phone;
    }

    // Getters and setters...
}
```
### Driver Class
Represents a driver in the system.
```java
public class Driver {
    private String driverId;
    private String name;
    private String vehicleDetails;

    public Driver(String driverId, String name, String vehicleDetails) {
        this.driverId = driverId;
        this.name = name;
        this.vehicleDetails = vehicleDetails;
    }

    // Getters and setters...
}
```
### Ride Class
Manages ride details.
```java
import java.util.Date;

public class Ride {
    private String rideId;
    private User user;
    private Driver driver;
    private Date rideDate;
    private double fare;

    public Ride(String rideId, User user, Driver driver, Date rideDate) {
        this.rideId = rideId;
        this.user = user;
        this.driver = driver;
        this.rideDate = rideDate;
    }

    public void setFare(double fare) {
        FareCalculator fareCalculator = new FareCalculator();
        this.fare = fareCalculator.calculateFare(distance, duration);
    }

    // Getters and setters...
}
```
### FareCalculator Class
Calculates the fare of a ride.
```java
public class FareCalculator {
    private static final double BASE_FARE = 2.50; // Base fare for a ride
    private static final double COST_PER_MILE = 1.50; // Cost per mile
    private static final double COST_PER_MINUTE = 0.25; // Cost per minute

    public double calculateFare(double distanceInMiles, double durationInMinutes) {
        double distanceCharge = distanceInMiles * COST_PER_MILE;
        double timeCharge = durationInMinutes * COST_PER_MINUTE;
        return BASE_FARE + distanceCharge + timeCharge;
    }
}
```
### RideSharingService Class
Manages the ride-sharing service operations.
```java
import java.util.ArrayList;
import java.util.List;
import java.util.Date;

public class RideSharingService {
    private List<User> users;
    private List<Driver> drivers;
    private List<Ride> rides;

    public RideSharingService() {
        this.users = new ArrayList<>();
        this.drivers = new ArrayList<>();
        this.rides = new ArrayList<>();
    }

    public Ride bookRide(User user, Driver driver, Date rideDate) {
        Ride newRide = new Ride(generateRideId(), user, driver, rideDate);
        FareCalculator fareCalculator = new FareCalculator();
        double fare = fareCalculator.calculateFare(newRide);
        newRide.setFare(fare);
        rides.add(newRide);
        return newRide;
    }

    private String generateRideId() {
        return "RIDE_" + System.currentTimeMillis();
    }
```
