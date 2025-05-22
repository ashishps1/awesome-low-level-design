public class ShippingCostCalculatorNaive {
    public double calculateShippingCost(Order order, String strategyType) {
        double cost = 0.0;

        if ("FLAT_RATE".equalsIgnoreCase(strategyType)) {
            System.out.println("Calculating with Flat Rate strategy.");
            cost = 10.0; // Fixed $10
        } else if ("WEIGHT_BASED".equalsIgnoreCase(strategyType)) {
            System.out.println("Calculating with Weight-Based strategy.");
            cost = order.getTotalWeight() * 2.5; // $2.5 per kg
        } else if ("DISTANCE_BASED".equalsIgnoreCase(strategyType)) {
            System.out.println("Calculating with Distance-Based strategy.");
            if ("ZoneA".equals(order.getDestinationZone())) {
                cost = 5.0;
            } else if ("ZoneB".equals(order.getDestinationZone())) {
                cost = 12.0;
            } else {
                cost = 20.0; // Default for other zones
            }
        } else if ("THIRD_PARTY_API".equalsIgnoreCase(strategyType)) {
            System.out.println("Calculating with Third-Party API strategy.");
            // Simulate API call
            cost = 7.5 + (order.getOrderValue() * 0.02); // Example: base fee + % of order value
        } else {
            throw new IllegalArgumentException("Unknown shipping strategy type: " + strategyType);
        }
        System.out.println("Calculated Shipping Cost: $" + cost);
        return cost;
    }    
}
