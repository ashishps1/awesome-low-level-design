using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace ConcertBookingSystem
{
    public class ConcertTicketBookingSystem
    {
        private static ConcertTicketBookingSystem _instance;
        private readonly ConcurrentDictionary<string, Concert> concerts;
        private readonly ConcurrentDictionary<string, Booking> bookings;
        private readonly object lockObject = new object();

        private ConcertTicketBookingSystem()
        {
            concerts = new ConcurrentDictionary<string, Concert>();
            bookings = new ConcurrentDictionary<string, Booking>();
        }

        public static ConcertTicketBookingSystem Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new ConcertTicketBookingSystem();
                }
                return _instance;
            }
        }

        public void AddConcert(Concert concert)
        {
            concerts.TryAdd(concert.Id, concert);
        }

        public Concert GetConcert(string concertId)
        {
            concerts.TryGetValue(concertId, out var concert);
            return concert;
        }

        public List<Concert> SearchConcerts(string artist, string venue, DateTime dateTime)
        {
            return concerts.Values.Where(concert =>
                concert.Artist.Equals(artist, StringComparison.OrdinalIgnoreCase) &&
                concert.Venue.Equals(venue, StringComparison.OrdinalIgnoreCase) &&
                concert.DateTime == dateTime).ToList();
        }

        public Booking BookTickets(User user, Concert concert, List<Seat> seats)
        {
            lock (lockObject)
            {
                foreach (var seat in seats)
                {
                    if (seat.Status != SeatStatus.AVAILABLE)
                    {
                        throw new SeatNotAvailableException($"Seat {seat.SeatNumber} is not available.");
                    }
                }

                seats.ForEach(seat => seat.Book());

                string bookingId = GenerateBookingId();
                var booking = new Booking(bookingId, user, concert, seats);
                bookings.TryAdd(bookingId, booking);

                ProcessPayment(booking);
                booking.ConfirmBooking();

                Console.WriteLine($"Booking {booking.Id} - {booking.Seats.Count} seats booked");

                return booking;
            }
        }

        public void CancelBooking(string bookingId)
        {
            bookings.TryRemove(bookingId, out var booking);
            booking?.CancelBooking();
        }

        private void ProcessPayment(Booking booking)
        {
            // Simulate payment processing logic here
        }

        private string GenerateBookingId()
        {
            return "BKG" + Guid.NewGuid();
        }
    }
}