class FlatRateFeeStrategy : IFeeStrategy
{
    private const double RATE_PER_HOUR = 10.0;

    public double CalculateFee(ParkingTicket parkingTicket)
    {
        long duration = parkingTicket.GetExitTimestamp() - parkingTicket.GetEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * RATE_PER_HOUR;
    }
}