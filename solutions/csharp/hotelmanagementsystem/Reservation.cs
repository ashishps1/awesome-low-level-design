using System;

namespace HotelManagement
{
    public class Reservation
    {
        public string Id { get; }
        public Guest Guest { get; }
        public Room Room { get; }
        public DateTime CheckInDate { get; }
        public DateTime CheckOutDate { get; }
        public ReservationStatus Status { get; private set; }

        public Reservation(string id, Guest guest, Room room, DateTime checkInDate, DateTime checkOutDate)
        {
            Id = id;
            Guest = guest;
            Room = room;
            CheckInDate = checkInDate;
            CheckOutDate = checkOutDate;
            Status = ReservationStatus.CONFIRMED;
        }

        public void Cancel()
        {
            if (Status == ReservationStatus.CONFIRMED)
            {
                Status = ReservationStatus.CANCELLED;
                Room.CheckOut();
            }
            else
            {
                throw new InvalidOperationException("Reservation is not confirmed.");
            }
        }
    }
}