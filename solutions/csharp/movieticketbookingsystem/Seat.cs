namespace MovieTicketBookingSystem
{
    public class Seat
    {
        public string Id { get; }
        public int Row { get; }
        public int Column { get; }
        public SeatType Type { get; }
        public double Price { get; }
        public SeatStatus Status { get; set; }

        public Seat(string id, int row, int column, SeatType type, double price, SeatStatus status)
        {
            Id = id;
            Row = row;
            Column = column;
            Type = type;
            Price = price;
            Status = status;
        }
    }
}