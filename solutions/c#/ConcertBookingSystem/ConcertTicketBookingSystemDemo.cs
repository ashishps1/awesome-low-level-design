using System;
using System.Collections.Generic;
using System.Linq;

namespace ConcertBookingSystem
{
    public class ConcertTicketBookingSystemDemo
    {
        public static void Run()
        {
            // Create concert ticket booking system instance
            var bookingSystem = ConcertTicketBookingSystem.Instance;

            // Create concerts
            var concert1Seats = GenerateSeats(100);
            var concert1 = new Concert("C001", "Artist 1", "Venue 1", DateTime.Now.AddDays(30), concert1Seats);
            bookingSystem.AddConcert(concert1);

            var concert2Seats = GenerateSeats(50);
            var concert2 = new Concert("C002", "Artist 2", "Venue 2", DateTime.Now.AddDays(60), concert2Seats);
            bookingSystem.AddConcert(concert2);

            // Create users
            var user1 = new User("U001", "John Doe", "john@example.com");
            var user2 = new User("U002", "Jane Smith", "jane@example.com");

            // Search concerts
            var searchResults = bookingSystem.SearchConcerts("Artist 1", "Venue 1", DateTime.Now.AddDays(30));
            Console.WriteLine("Search Results:");
            foreach (var concert in searchResults)
            {
                Console.WriteLine($"Concert: {concert.Artist} at {concert.Venue}");
            }

            // Book tickets
            var selectedSeats1 = SelectSeats(concert1, 3);
            var booking1 = bookingSystem.BookTickets(user1, concert1, selectedSeats1);

            var selectedSeats2 = SelectSeats(concert2, 2);
            var booking2 = bookingSystem.BookTickets(user2, concert2, selectedSeats2);

            // Cancel booking
            bookingSystem.CancelBooking(booking1.Id);

            // Book tickets again
            var selectedSeats3 = SelectSeats(concert1, 2);
            var booking3 = bookingSystem.BookTickets(user2, concert1, selectedSeats3);
        }

        private static List<Seat> GenerateSeats(int numberOfSeats)
        {
            var seats = new List<Seat>();
            for (int i = 1; i <= numberOfSeats; i++)
            {
                string seatNumber = "S" + i;
                SeatType seatType = (i <= 10) ? SeatType.VIP : (i <= 30) ? SeatType.PREMIUM : SeatType.REGULAR;
                double price = seatType switch
                {
                    SeatType.VIP => 100.0,
                    SeatType.PREMIUM => 75.0,
                    _ => 50.0,
                };
                seats.Add(new Seat(seatNumber, seatNumber, seatType, price));
            }
            return seats;
        }

        private static List<Seat> SelectSeats(Concert concert, int numberOfSeats)
        {
            var availableSeats = concert.Seats
                .Where(seat => seat.Status == SeatStatus.AVAILABLE)
                .Take(numberOfSeats)
                .ToList();
            return availableSeats;
        }
    }
}