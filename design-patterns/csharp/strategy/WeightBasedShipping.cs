namespace Strategy
{
    public class WeightBasedShipping : IShippingStrategy
    {
        private const double RATE_PER_KG = 2.0;

        public double CalculateCost(Order order)
        {
            return order.GetTotalWeight() * RATE_PER_KG;
        }
    }
} 