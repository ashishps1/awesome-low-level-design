public class ECommerceAppV2 {
    public static void main(String[] args) {
        Order order1 = new Order();

        // Create different strategy instances
        ShippingStrategy flatRate = new FlatRateShipping(10.0);
        ShippingStrategy weightBased = new WeightBasedShipping(2.5);
        ShippingStrategy distanceBased = new DistanceBasedShipping(5.0);
        ShippingStrategy thirdParty = new ThirdPartyApiShipping(7.5, 0.02);

        // Create context with an initial strategy
        ShippingCostService shippingService = new ShippingCostService(flatRate);

        System.out.println("--- Order 1: Using Flat Rate (initial) ---");
        shippingService.calculateShippingCost(order1);

        System.out.println("\n--- Order 1: Changing to Weight-Based ---");
        shippingService.setStrategy(weightBased);
        shippingService.calculateShippingCost(order1);

        System.out.println("\n--- Order 1: Changing to Distance-Based ---");
        shippingService.setStrategy(distanceBased);
        shippingService.calculateShippingCost(order1);

        System.out.println("\n--- Order 1: Changing to Third-Party API ---");
        shippingService.setStrategy(thirdParty);
        shippingService.calculateShippingCost(order1);

        // Adding a NEW strategy is easy:
        // 1. Create a new class implementing ShippingStrategy (e.g., FreeShippingStrategy)
        // 2. Client can then instantiate and use it:
        //    ShippingStrategy freeShipping = new FreeShippingStrategy();
        //    shippingService.setStrategy(freeShipping);
        //    shippingService.calculateShippingCost(primeMemberOrder);
        // No modification to ShippingCostService is needed!
    }    
}
