enum SeatType
{
    REGULAR,
    PREMIUM,
    RECLINER
}

static class SeatTypeExtensions
{
    public static double GetPrice(this SeatType seatType)
    {
        switch (seatType)
        {
            case SeatType.REGULAR: return 50.0;
            case SeatType.PREMIUM: return 80.0;
            case SeatType.RECLINER: return 120.0;
            default: return 50.0;
        }
    }
}