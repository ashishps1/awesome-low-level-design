package carrentalsystem;

import java.time.LocalDate;
import java.util.List;

public class CarRentalSystemDemo {
    public static void run() {
        RentalSystem rentalSystem = RentalSystem.getInstance();

        // Add cars to the rental system
        rentalSystem.addCar(new Car("Toyota", "Camry", 2022, "ABC123", 50.0));
        rentalSystem.addCar(new Car("Honda", "Civic", 2021, "XYZ789", 45.0));
        rentalSystem.addCar(new Car("Ford", "Mustang", 2023, "DEF456", 80.0));

        // Create customers
        Customer customer1 = new Customer("John Doe", "john@example.com", "DL1234");

        // Make reservations
        LocalDate startDate = LocalDate.now();
        LocalDate endDate = startDate.plusDays(3);
        List<Car> availableCars = rentalSystem.searchCars("Toyota", "Camry", startDate, endDate);
        if (!availableCars.isEmpty()) {
            Car selectedCar = availableCars.getFirst();
            Reservation reservation = rentalSystem.makeReservation(customer1, selectedCar, startDate, endDate);
            if (reservation != null) {
                boolean paymentSuccess = rentalSystem.processPayment(reservation);
                if (paymentSuccess) {
                    System.out.println("Reservation successful. Reservation ID: " + reservation.getReservationId());
                } else {
                    System.out.println("Payment failed. Reservation canceled.");
                    rentalSystem.cancelReservation(reservation.getReservationId());
                }
            } else {
                System.out.println("Selected car is not available for the given dates.");
            }
        } else {
            System.out.println("No available cars found for the given criteria.");
        }
    }
}
