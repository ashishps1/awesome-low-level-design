class Bid : IComparable<Bid>
{
    private readonly User bidder;
    private readonly decimal amount;
    private readonly DateTime timestamp;

    public Bid(User bidder, decimal amount)
    {
        this.bidder = bidder;
        this.amount = amount;
        this.timestamp = DateTime.Now;
    }

    public User GetBidder()
    {
        return bidder;
    }

    public decimal GetAmount()
    {
        return amount;
    }

    public DateTime GetTimestamp()
    {
        return timestamp;
    }

    public int CompareTo(Bid other)
    {
        int amountComparison = amount.CompareTo(other.amount);
        if (amountComparison != 0)
        {
            return amountComparison;
        }
        return other.timestamp.CompareTo(timestamp);
    }

    public override string ToString()
    {
        return $"Bidder: {bidder.GetName()}, Amount: {amount:F2}, Time: {timestamp}";
    }
}