class VehicleBasedFeeStrategy : IFeeStrategy
{
    private static readonly Dictionary<VehicleSize, double> HOURLY_RATES = new Dictionary<VehicleSize, double>
    {
        { VehicleSize.SMALL, 10.0 },
        { VehicleSize.MEDIUM, 20.0 },
        { VehicleSize.LARGE, 30.0 }
    };

    public double CalculateFee(ParkingTicket parkingTicket)
    {
        long duration = parkingTicket.GetExitTimestamp() - parkingTicket.GetEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * HOURLY_RATES[parkingTicket.GetVehicle().GetSize()];
    }
}