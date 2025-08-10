class CreditCardPaymentStrategy : IPaymentStrategy
{
    private readonly string cardNumber;

    public CreditCardPaymentStrategy(string cardNumber)
    {
        this.cardNumber = cardNumber;
    }

    public bool Pay(double amount)
    {
        Console.WriteLine($"Processing credit card payment of ${amount:F2} with card {cardNumber}.");
        return true;
    }
}