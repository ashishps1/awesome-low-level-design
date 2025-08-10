class CreditCardPaymentStrategy : IPaymentStrategy
{
    private readonly string cardNumber;
    private readonly string cvv;

    public CreditCardPaymentStrategy(string cardNumber, string cvv)
    {
        this.cardNumber = cardNumber;
        this.cvv = cvv;
    }

    public Payment Pay(double amount)
    {
        Console.WriteLine($"Processing credit card payment of ${amount:F2}");
        // Simulate payment gateway interaction
        var random = new Random();
        bool paymentSuccess = random.NextDouble() > 0.05; // 95% success rate
        
        return new Payment(
            amount,
            paymentSuccess ? PaymentStatus.SUCCESS : PaymentStatus.FAILURE,
            $"TXN_{Guid.NewGuid()}"
        );
    }
}