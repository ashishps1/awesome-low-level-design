using System;
using System.Collections.Generic;

namespace CarRentalSystem
{
    public class CarRentalSystemDemo
    {
        public static void Run()
        {
            var rentalSystem = RentalSystem.Instance;

            // Add cars to the rental system
            rentalSystem.AddCar(new Car("Toyota", "Camry", 2022, "ABC123", 50.0));
            rentalSystem.AddCar(new Car("Honda", "Civic", 2021, "XYZ789", 45.0));
            rentalSystem.AddCar(new Car("Ford", "Mustang", 2023, "DEF456", 80.0));

            // Create customers
            var customer1 = new Customer("John Doe", "john@example.com", "DL1234");

            // Make reservations
            var startDate = DateTime.Now;
            var endDate = startDate.AddDays(3);
            List<Car> availableCars = rentalSystem.SearchCars("Toyota", "Camry", startDate, endDate);
            if (availableCars.Count > 0)
            {
                Car selectedCar = availableCars[0];
                var reservation = rentalSystem.MakeReservation(customer1, selectedCar, startDate, endDate);
                if (reservation != null)
                {
                    bool paymentSuccess = rentalSystem.ProcessPayment(reservation);
                    if (paymentSuccess)
                    {
                        Console.WriteLine("Reservation successful. Reservation ID: " + reservation.ReservationId);
                    }
                    else
                    {
                        Console.WriteLine("Payment failed. Reservation canceled.");
                        rentalSystem.CancelReservation(reservation.ReservationId);
                    }
                }
                else
                {
                    Console.WriteLine("Selected car is not available for the given dates.");
                }
            }
            else
            {
                Console.WriteLine("No available cars found for the given criteria.");
            }
        }
    }
}