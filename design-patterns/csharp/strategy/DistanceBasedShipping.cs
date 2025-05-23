namespace Strategy
{
    public class DistanceBasedShipping : IShippingStrategy
    {
        private const double BASE_RATE = 5.0;
        private const double ZONE_A_MULTIPLIER = 1.0;
        private const double ZONE_B_MULTIPLIER = 1.5;
        private const double ZONE_C_MULTIPLIER = 2.0;

        public double CalculateCost(Order order)
        {
            double multiplier = order.GetDestinationZone() switch
            {
                "ZoneA" => ZONE_A_MULTIPLIER,
                "ZoneB" => ZONE_B_MULTIPLIER,
                "ZoneC" => ZONE_C_MULTIPLIER,
                _ => ZONE_A_MULTIPLIER
            };

            return BASE_RATE * multiplier;
        }
    }
} 