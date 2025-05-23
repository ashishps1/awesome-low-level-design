using System;

namespace Adapter
{
    class Program
    {
        static void Main(string[] args)
        {
            // Example 1: Using the in-house payment processor
            Console.WriteLine("=== Using In-House Payment Processor ===");
            var inHouseProcessor = new InHousePaymentProcessor();
            var checkoutService1 = new CheckoutService(inHouseProcessor);
            checkoutService1.Checkout(100.00, "USD");

            Console.WriteLine("\n=== Using Legacy Gateway Adapter ===");
            var legacyAdapter = new LegacyGatewayAdapter();
            var checkoutService2 = new CheckoutService(legacyAdapter);
            checkoutService2.Checkout(200.00, "EUR");
        }
    }
} 