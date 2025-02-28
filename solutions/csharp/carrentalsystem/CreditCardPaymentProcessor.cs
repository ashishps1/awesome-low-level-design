namespace CarRentalSystem
{
    public class CreditCardPaymentProcessor : IPaymentProcessor
    {
        public bool ProcessPayment(double amount)
        {
            // Simulate processing payment
            // Actual implementation would involve integrating with a payment gateway
            return true;
        }
    }
}