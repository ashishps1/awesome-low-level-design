class Payment
{
    private readonly string id;
    private readonly double amount;
    private readonly PaymentStatus status;
    private readonly string transactionId;

    public Payment(double amount, PaymentStatus status, string transactionId)
    {
        this.id = Guid.NewGuid().ToString();
        this.amount = amount;
        this.status = status;
        this.transactionId = transactionId;
    }

    public PaymentStatus GetStatus() { return status; }
}