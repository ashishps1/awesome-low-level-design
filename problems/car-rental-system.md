# Designing a Car Rental System

In this article, we will explore the object-oriented design and implementation of a Car Rental System (CRS) using Java. 

This system will handle the renting of cars to customers, managing car inventory, and tracking rentals.

## System Requirements

The CRS should support:

1. **Car Inventory Management:** Keep track of available cars for rent.
2. **Rental Process Management:** Handle the process of renting a car to a customer.
3. **Rental Tracking:** Track ongoing and past rentals.
4. **Customer Management:** Manage customer information.

## Core Use Cases

1. **Renting a Car:** Customers can rent available cars.
2. **Returning a Car:** Handle the return process of rented cars.
3. **Tracking Rentals:** View current and past rental records.
4. **Managing Car Inventory:** Add, update, and remove cars from the inventory.

## Key Classes:
- `CarRentalSystem`: Manages the overall operations of the car rental system.
- `Car`: Represents a car in the system.
- `Rental`: Manages details about a car rental.
- `Customer`: Stores information about customers.

## Java Implementation

### Car Class

```java
public class Car {
    private String licensePlate;
    private String make;
    private boolean isAvailable;

    public Car(String licensePlate, String make) {
        this.licensePlate = licensePlate;
        this.make = make;
        this.isAvailable = true;
    }

    public void rentOut() {
        isAvailable = false;
    }

    public void returnCar() {
        isAvailable = true;
    }

    // Getters and setters...
}
```
### Customer Class
```java
public class Customer {
    private String customerId;
    private String name;

    public Customer(String customerId, String name) {
        this.customerId = customerId;
        this.name = name;
    }

    // Getters and setters...
}
```
### Rental Class
```java
import java.time.LocalDate;

public class Rental {
    private Car car;
    private Customer customer;
    private LocalDate rentalDate;
    private LocalDate returnDate;

    public Rental(Car car, Customer customer, LocalDate rentalDate) {
        this.car = car;
        this.customer = customer;
        this.rentalDate = rentalDate;
        this.car.rentOut();
    }

    public void completeRental(LocalDate returnDate) {
        this.returnDate = returnDate;
        this.car.returnCar();
    }

    // Getters and setters...
}
```
### CarRentalSystem Class
```java
import java.util.ArrayList;
import java.util.List;

public class CarRentalSystem {
    private List<Car> cars;
    private List<Rental> rentals;

    public CarRentalSystem() {
        cars = new ArrayList<>();
        rentals = new ArrayList<>();
    }

    public void addCar(Car car) {
        cars.add(car);
    }

    public Rental rentCar(String licensePlate, Customer customer, LocalDate rentalDate) {
        Car car = findAvailableCar(licensePlate);
        if (car != null) {
            Rental rental = new Rental(car, customer, rentalDate);
            rentals.add(rental);
            return rental;
        }
        return null;
    }

    private Car findAvailableCar(String licensePlate) {
        return cars.stream()
                   .filter(c -> c.getLicensePlate().equals(licensePlate) && c.isAvailable())
                   .findFirst().orElse(null);
    }

    // Other necessary methods...
}
```
