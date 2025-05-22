public class ECommerceAppV1 {
    public static void main(String[] args) {
        ShippingCostCalculatorNaive calculator = new ShippingCostCalculatorNaive();
        Order order1 = new Order();

        System.out.println("--- Order 1 ---");
        calculator.calculateShippingCost(order1, "FLAT_RATE");
        calculator.calculateShippingCost(order1, "WEIGHT_BASED");
        calculator.calculateShippingCost(order1, "DISTANCE_BASED");
        calculator.calculateShippingCost(order1, "THIRD_PARTY_API");

        // What if we want to try a new "PremiumZone" strategy?
        // We have to modify the ShippingCostCalculatorNaive class!
    }    
}
