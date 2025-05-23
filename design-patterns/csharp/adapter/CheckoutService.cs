using System;

namespace Adapter
{
    public class CheckoutService
    {
        private readonly IPaymentProcessor paymentProcessor;

        public CheckoutService(IPaymentProcessor paymentProcessor)
        {
            this.paymentProcessor = paymentProcessor;
        }

        public bool Checkout(double amount, string currency)
        {
            Console.WriteLine($"CheckoutService: Initiating checkout for {currency} {amount}");
            
            paymentProcessor.ProcessPayment(amount, currency);
            
            if (paymentProcessor.IsPaymentSuccessful())
            {
                Console.WriteLine($"CheckoutService: Payment successful. Transaction ID: {paymentProcessor.GetTransactionId()}");
                return true;
            }
            
            Console.WriteLine("CheckoutService: Payment failed.");
            return false;
        }
    }
} 