namespace Adapter
{
    public interface IPaymentProcessor
    {
        void ProcessPayment(double amount, string currency);
        bool IsPaymentSuccessful();
        string GetTransactionId();
    }
} 