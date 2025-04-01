namespace CarRentalSystem
{
    public interface IPaymentProcessor
    {
        bool ProcessPayment(double amount);
    }
}