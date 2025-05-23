namespace Strategy
{
    public class ThirdPartyApiShipping : IShippingStrategy
    {
        public double CalculateCost(Order order)
        {
            // Simulate API call to third-party shipping service
            double baseRate = 15.0;
            double weightFactor = order.GetTotalWeight() * 1.5;
            double distanceFactor = order.GetDestinationZone() == "ZoneC" ? 2.0 : 1.0;

            return baseRate + weightFactor * distanceFactor;
        }
    }
} 