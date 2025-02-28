using System.Collections.Generic;

namespace MovieTicketBookingSystem
{
    public class Booking
    {
        public string Id { get; }
        public User User { get; }
        public Show Show { get; }
        public List<Seat> Seats { get; }
        public double TotalPrice { get; }
        public BookingStatus Status { get; set; }

        public Booking(string id, User user, Show show, List<Seat> seats, double totalPrice, BookingStatus status)
        {
            Id = id;
            User = user;
            Show = show;
            Seats = seats;
            TotalPrice = totalPrice;
            Status = status;
        }
    }
}