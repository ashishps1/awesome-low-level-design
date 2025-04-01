namespace AirlineManagementSystem
{
    public class Seat
    {
        public string SeatNumber { get; }
        public SeatType Type { get; }
        public SeatStatus Status { get; private set; }

        public Seat(string seatNumber, SeatType type)
        {
            SeatNumber = seatNumber;
            Type = type;
            Status = SeatStatus.AVAILABLE;
        }

        public void Reserve()
        {
            Status = SeatStatus.RESERVED;
        }

        public void Release()
        {
            Status = SeatStatus.AVAILABLE;
        }
    }
}