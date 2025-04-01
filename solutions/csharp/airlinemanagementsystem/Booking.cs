using System;

namespace AirlineManagementSystem
{
    public class Booking
    {
        public string BookingNumber { get; }
        public Flight Flight { get; }
        public Passenger Passenger { get; }
        public Seat Seat { get; }
        public double Price { get; }
        public BookingStatus Status { get; private set; }

        public Booking(string bookingNumber, Flight flight, Passenger passenger, Seat seat, double price)
        {
            BookingNumber = bookingNumber;
            Flight = flight;
            Passenger = passenger;
            Seat = seat;
            Price = price;
            Status = BookingStatus.CONFIRMED;
        }

        public void Cancel()
        {
            Status = BookingStatus.CANCELLED;
        }
    }
}