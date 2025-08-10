class PaymentService
{
    public bool ProcessPayment(IPaymentStrategy strategy, double amount)
    {
        return strategy.Pay(amount);
    }
}