class UPIPaymentStrategy : IPaymentStrategy
{
    private readonly string upiId;

    public UPIPaymentStrategy(string upiId)
    {
        this.upiId = upiId;
    }

    public bool Pay(double amount)
    {
        Console.WriteLine($"Processing UPI payment of ${amount:F2} with upi id {upiId}.");
        return true;
    }
}