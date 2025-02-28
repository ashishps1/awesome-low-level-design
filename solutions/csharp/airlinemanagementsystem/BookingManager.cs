using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading;

namespace AirlineManagementSystem
{
    public class BookingManager
    {
        private static BookingManager instance;
        private readonly Dictionary<string, Booking> bookings = new Dictionary<string, Booking>();
        private readonly object lockObject = new object();
        private static int bookingCounter = 0;

        private BookingManager() { }

        public static BookingManager Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new BookingManager();
                }
                return instance;
            }
        }

        public Booking CreateBooking(Flight flight, Passenger passenger, Seat seat, double price)
        {
            string bookingNumber = GenerateBookingNumber();
            var booking = new Booking(bookingNumber, flight, passenger, seat, price);
            lock (lockObject)
            {
                bookings[bookingNumber] = booking;
            }
            return booking;
        }

        public void CancelBooking(string bookingNumber)
        {
            lock (lockObject)
            {
                if (bookings.TryGetValue(bookingNumber, out var booking))
                {
                    booking.Cancel();
                }
            }
        }

        private string GenerateBookingNumber()
        {
            int bookingId = Interlocked.Increment(ref bookingCounter);
            string timestamp = DateTime.Now.ToString("yyyyMMddHHmmss", CultureInfo.InvariantCulture);
            return $"BKG{timestamp}{bookingId:D6}";
        }
    }
}