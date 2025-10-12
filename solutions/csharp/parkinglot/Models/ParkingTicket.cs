class ParkingTicket
{
    private readonly string ticketId;
    private readonly Vehicle vehicle;
    private readonly ParkingSpot spot;
    private readonly long entryTimestamp;
    private long exitTimestamp;

    public ParkingTicket(Vehicle vehicle, ParkingSpot spot)
    {
        this.ticketId = Guid.NewGuid().ToString();
        this.vehicle = vehicle;
        this.spot = spot;
        this.entryTimestamp = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
        this.exitTimestamp = 0;
    }

    public string GetTicketId() { return ticketId; }
    public Vehicle GetVehicle() { return vehicle; }
    public ParkingSpot GetSpot() { return spot; }
    public long GetEntryTimestamp() { return entryTimestamp; }
    public long GetExitTimestamp() { return exitTimestamp; }

    public void SetExitTimestamp()
    {
        this.exitTimestamp = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
    }
}