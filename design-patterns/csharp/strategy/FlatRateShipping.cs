namespace Strategy
{
    public class FlatRateShipping : IShippingStrategy
    {
        private const double FLAT_RATE = 10.0;

        public double CalculateCost(Order order)
        {
            return FLAT_RATE;
        }
    }
} 