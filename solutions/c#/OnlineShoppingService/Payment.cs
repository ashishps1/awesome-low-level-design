namespace OnlineShopping
{
    public interface Payment
    {
        bool ProcessPayment(double amount);
    }
}