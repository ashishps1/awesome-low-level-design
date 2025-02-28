using System;
using System.Collections.Generic;

namespace AirlineManagementSystem
{
    public class AirlineManagementSystemDemo
    {
        public static void Run()
        {
            var airlineManagementSystem = new AirlineManagementSystem();

            // Create users
            var passenger1 = new Passenger("U001", "John Doe", "john@example.com", "1234567890");

            // Create flights
            var departureTime1 = DateTime.Now.AddDays(1);
            var arrivalTime1 = departureTime1.AddHours(2);
            var flight1 = new Flight("F001", "New York", "London", departureTime1, arrivalTime1);

            var departureTime2 = DateTime.Now.AddDays(3);
            var arrivalTime2 = departureTime2.AddHours(5);
            var flight2 = new Flight("F002", "Paris", "Tokyo", departureTime2, arrivalTime2);

            airlineManagementSystem.AddFlight(flight1);
            airlineManagementSystem.AddFlight(flight2);

            // Create aircrafts
            var aircraft1 = new Aircraft("A001", "Boeing 747", 300);
            var aircraft2 = new Aircraft("A002", "Airbus A380", 500);
            airlineManagementSystem.AddAircraft(aircraft1);
            airlineManagementSystem.AddAircraft(aircraft2);

            // Search flights
            var searchResults = airlineManagementSystem.SearchFlights("New York", "London", DateTime.Now.AddDays(1));
            Console.WriteLine("Search Results:");
            foreach (var flight in searchResults)
            {
                Console.WriteLine($"Flight: {flight.FlightNumber} - {flight.Source} to {flight.Destination}");
            }

            var seat = new Seat("25A", SeatType.ECONOMY);

            // Book a flight
            var booking = airlineManagementSystem.BookFlight(flight1, passenger1, seat, 100);
            if (booking != null)
            {
                Console.WriteLine("Booking successful. Booking ID: " + booking.BookingNumber);
            }
            else
            {
                Console.WriteLine("Booking failed.");
            }

            // Cancel a booking
            airlineManagementSystem.CancelBooking(booking.BookingNumber);
            Console.WriteLine("Booking cancelled.");
        }
    }
}