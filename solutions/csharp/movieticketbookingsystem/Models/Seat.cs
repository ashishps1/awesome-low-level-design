class Seat
{
    private readonly string id;
    private readonly int row;
    private readonly int col;
    private readonly SeatType type;
    private SeatStatus status;

    public Seat(string id, int row, int col, SeatType type)
    {
        this.id = id;
        this.row = row;
        this.col = col;
        this.type = type;
        this.status = SeatStatus.AVAILABLE;
    }

    public string GetId() { return id; }
    public int GetRow() { return row; }
    public int GetCol() { return col; }
    public SeatType GetSeatType() { return type; }
    public SeatStatus GetStatus() { return status; }
    public void SetStatus(SeatStatus status) { this.status = status; }
}