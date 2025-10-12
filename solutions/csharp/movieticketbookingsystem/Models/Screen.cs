class Screen
{
    private readonly string id;
    private readonly List<Seat> seats;

    public Screen(string id)
    {
        this.id = id;
        this.seats = new List<Seat>();
    }

    public void AddSeat(Seat seat)
    {
        seats.Add(seat);
    }

    public string GetId() { return id; }
    public List<Seat> GetSeats() { return seats; }
}