namespace ConcertBookingSystem
{
    public class Seat
    {
        public string Id { get; }
        public string SeatNumber { get; }
        public SeatType SeatType { get; }
        public double Price { get; }
        public SeatStatus Status { get; private set; }

        public Seat(string id, string seatNumber, SeatType seatType, double price)
        {
            Id = id;
            SeatNumber = seatNumber;
            SeatType = seatType;
            Price = price;
            Status = SeatStatus.AVAILABLE;
        }

        public void Book()
        {
            if (Status == SeatStatus.AVAILABLE)
            {
                Status = SeatStatus.BOOKED;
            }
            else
            {
                throw new SeatNotAvailableException("Seat is already booked or reserved.");
            }
        }

        public void Release()
        {
            if (Status == SeatStatus.BOOKED)
            {
                Status = SeatStatus.AVAILABLE;
            }
        }
    }
}