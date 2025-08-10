class WeekdayPricingStrategy : IPricingStrategy
{
    public double CalculatePrice(List<Seat> seats)
    {
        return seats.Sum(seat => seat.GetSeatType().GetPrice());
    }
}