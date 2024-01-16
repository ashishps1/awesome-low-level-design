# Designing a Vehicle Rental System

In this article, we explore the object-oriented design and implementation of a Vehicle Rental System using Java. 

This system facilitates the renting of vehicles for short and long durations.

## System Requirements

The Vehicle Rental System should:

1. **Vehicle Management**: Handle various types of vehicles available for rent.
2. **User Account Management**: Manage customer registrations and profiles.
3. **Rental Process**: Enable users to rent and return vehicles.
4. **Pricing and Payment**: Calculate rental charges and process payments.
5. **Reservation System**: Support advance booking of vehicles.

## Core Use Cases

1. **Adding and Managing Vehicles**
2. **Registering and Managing User Accounts**
3. **Renting and Returning Vehicles**
4. **Calculating Rental Charges**
5. **Handling Reservations**

## Key Classes:
- `VehicleRentalSystem`: Manages the overall system.
- `User`: Represents a system user or customer.
- `Vehicle`: Abstract class for various types of vehicles.
- `Rental`: Represents a vehicle rental transaction.

## Java Implementation

### Vehicle Class (Abstract)

Represents a generic vehicle.

```java
public abstract class Vehicle {
    private String vehicleId;
    private String model;
    private double ratePerDay;

    public Vehicle(String vehicleId, String model, double ratePerDay) {
        this.vehicleId = vehicleId;
        this.model = model;
        this.ratePerDay = ratePerDay;
    }

    // Getters and setters...
}
```
### User Class
Manages user account information.
```java
public class User {
    private String userId;
    private String name;
    private String driverLicenseNumber;

    public User(String userId, String name, String driverLicenseNumber) {
        this.userId = userId;
        this.name = name;
        this.driverLicenseNumber = driverLicenseNumber;
    }

    // Getters and setters...
}
```
### Rental Class
Represents a vehicle rental transaction.
```java
import java.util.Date;

public class Rental {
    private String rentalId;
    private User user;
    private Vehicle vehicle;
    private Date rentalDate;
    private Date returnDate;
    private double totalCharge;

    public Rental(String rentalId, User user, Vehicle vehicle, Date rentalDate) {
        this.rentalId = rentalId;
        this.user = user;
        this.vehicle = vehicle;
        this.rentalDate = rentalDate;
    }

    public void completeRental(Date returnDate) {
        this.returnDate = returnDate;
        this.totalCharge = calculateTotalCharge();
    }

    private double calculateTotalCharge() {
        // Calculate total charge based on rental duration and vehicle rate
        long rentalDays = (returnDate.getTime() - rentalDate.getTime()) / (1000 * 60 * 60 * 24);
        return rentalDays * vehicle.getRatePerDay();
    }

    // Getters and setters...
}
```
### VehicleRentalSystem Class
Manages the vehicle rental system operations.
```java
import java.util.ArrayList;
import java.util.List;

public class VehicleRentalSystem {
    private List<User> users;
    private List<Vehicle> vehicles;
    private List<Rental> rentals;

    public VehicleRentalSystem() {
        this.users = new ArrayList<>();
        this.vehicles = new ArrayList<>();
        this.rentals = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public void addVehicle(Vehicle vehicle) {
        vehicles.add(vehicle);
    }

    public Rental rentVehicle(String userId, String vehicleId, Date rentalDate) {
        User user = findUserById(userId);
        Vehicle vehicle = findVehicleById(vehicleId);

        if (user != null && vehicle != null) {
            Rental rental = new Rental(generateRentalId(), user, vehicle, rentalDate);
            rentals.add(rental);
            return rental;
        }
        return null;
    }

    public void returnVehicle(String rentalId, Date returnDate) {
        Rental rental = findRentalById(rentalId);
        if (rental != null) {
            rental.completeRental(returnDate);
        }
    }

    private User findUserById(String userId) {
        for (User user : users) {
            if (user.getUserId().equals(userId)) {
                return user;
            }
        }
        return null;
    }

    private Vehicle findVehicleById(String vehicleId) {
        for (Vehicle vehicle : vehicles) {
            if (vehicle.getVehicleId().equals(vehicleId)) {
                return vehicle;
            }
        }
        return null;
    }

    private Rental findRentalById(String rentalId) {
        for (Rental rental : rentals) {
            if (rental.getRentalId().equals(rentalId)) {
                return rental;
            }
        }
        return null;
    }

    private String generateRentalId() {
        return "RENTAL_" + System.currentTimeMillis();
    }
    
    // Other necessary methods...
```