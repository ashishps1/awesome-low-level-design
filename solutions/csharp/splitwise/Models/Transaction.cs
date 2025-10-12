class Transaction
{
    private readonly User from;
    private readonly User to;
    private readonly double amount;

    public Transaction(User from, User to, double amount)
    {
        this.from = from;
        this.to = to;
        this.amount = amount;
    }

    public override string ToString()
    {
        return $"{from.GetName()} should pay {to.GetName()} ${amount:F2}";
    }
}