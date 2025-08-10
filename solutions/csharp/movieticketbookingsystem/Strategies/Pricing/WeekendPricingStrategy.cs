class WeekendPricingStrategy : IPricingStrategy
{
    private const double WEEKEND_SURCHARGE = 1.2; // 20% surcharge

    public double CalculatePrice(List<Seat> seats)
    {
        double basePrice = seats.Sum(seat => seat.GetSeatType().GetPrice());
        return basePrice * WEEKEND_SURCHARGE;
    }
}