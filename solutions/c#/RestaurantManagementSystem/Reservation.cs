using System;

namespace RestaurantManagementSystem
{
    public class Reservation
    {
        public int Id { get; }
        public string CustomerName { get; }
        public string ContactNumber { get; }
        public int PartySize { get; }
        public DateTime ReservationTime { get; }

        public Reservation(int id, string customerName, string contactNumber, int partySize, DateTime reservationTime)
        {
            Id = id;
            CustomerName = customerName;
            ContactNumber = contactNumber;
            PartySize = partySize;
            ReservationTime = reservationTime;
        }
    }
}