using System;
using System.Collections.Generic;

namespace ConcertBookingSystem
{
    public class Booking
    {
        public string Id { get; }
        public User User { get; }
        public Concert Concert { get; }
        public List<Seat> Seats { get; }
        public double TotalPrice { get; }
        public BookingStatus Status { get; private set; }

        public Booking(string id, User user, Concert concert, List<Seat> seats)
        {
            Id = id;
            User = user;
            Concert = concert;
            Seats = seats;
            TotalPrice = CalculateTotalPrice();
            Status = BookingStatus.PENDING;
        }

        private double CalculateTotalPrice()
        {
            return Seats.Sum(seat => seat.Price);
        }

        public void ConfirmBooking()
        {
            if (Status == BookingStatus.PENDING)
            {
                Status = BookingStatus.CONFIRMED;
                // Send booking confirmation
            }
        }

        public void CancelBooking()
        {
            if (Status == BookingStatus.CONFIRMED)
            {
                Status = BookingStatus.CANCELLED;
                Seats.ForEach(seat => seat.Release());
                Console.WriteLine($"Booking {Id} cancelled");
            }
        }
    }
}