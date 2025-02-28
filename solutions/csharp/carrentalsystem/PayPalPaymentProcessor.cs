namespace CarRentalSystem
{
    public class PayPalPaymentProcessor : IPaymentProcessor
    {
        public bool ProcessPayment(double amount)
        {
            // Simulate processing PayPal payment
            return true;
        }
    }
}