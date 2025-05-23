namespace Strategy
{
    public class ShippingCostService
    {
        private readonly IShippingStrategy shippingStrategy;

        public ShippingCostService(IShippingStrategy shippingStrategy)
        {
            this.shippingStrategy = shippingStrategy;
        }

        public double CalculateShippingCost(Order order)
        {
            return shippingStrategy.CalculateCost(order);
        }
    }
} 