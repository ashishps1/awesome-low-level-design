using System;

namespace Strategy
{
    class Program
    {
        static void Main(string[] args)
        {
            var order = new Order();

            // Using different shipping strategies
            var flatRateService = new ShippingCostService(new FlatRateShipping());
            var weightBasedService = new ShippingCostService(new WeightBasedShipping());
            var distanceBasedService = new ShippingCostService(new DistanceBasedShipping());
            var thirdPartyService = new ShippingCostService(new ThirdPartyApiShipping());

            Console.WriteLine("Shipping costs using different strategies:");
            Console.WriteLine($"Flat Rate Shipping: ${flatRateService.CalculateShippingCost(order):F2}");
            Console.WriteLine($"Weight Based Shipping: ${weightBasedService.CalculateShippingCost(order):F2}");
            Console.WriteLine($"Distance Based Shipping: ${distanceBasedService.CalculateShippingCost(order):F2}");
            Console.WriteLine($"Third Party API Shipping: ${thirdPartyService.CalculateShippingCost(order):F2}");
        }
    }
} 