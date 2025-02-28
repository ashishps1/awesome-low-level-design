namespace HotelManagement
{
    public class Room
    {
        public string Id { get; }
        public RoomType Type { get; }
        public double Price { get; }
        public RoomStatus Status { get; private set; }

        public Room(string id, RoomType type, double price)
        {
            Id = id;
            Type = type;
            Price = price;
            Status = RoomStatus.AVAILABLE;
        }

        public void Book()
        {
            if (Status == RoomStatus.AVAILABLE)
            {
                Status = RoomStatus.BOOKED;
            }
            else
            {
                throw new InvalidOperationException("Room is not available for booking.");
            }
        }

        public void CheckIn()
        {
            if (Status == RoomStatus.BOOKED)
            {
                Status = RoomStatus.OCCUPIED;
            }
            else
            {
                throw new InvalidOperationException("Room is not booked.");
            }
        }

        public void CheckOut()
        {
            if (Status == RoomStatus.OCCUPIED)
            {
                Status = RoomStatus.AVAILABLE;
            }
            else
            {
                throw new InvalidOperationException("Room is not occupied.");
            }
        }
    }
}