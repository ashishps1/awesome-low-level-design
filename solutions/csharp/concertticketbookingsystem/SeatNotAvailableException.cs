using System;

namespace ConcertBookingSystem
{
    public class SeatNotAvailableException : Exception
    {
        public SeatNotAvailableException(string message) : base(message)
        {
        }
    }
}