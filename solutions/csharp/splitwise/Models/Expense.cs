class Expense
{
    private readonly string id;
    private readonly string description;
    private readonly double amount;
    private readonly User paidBy;
    private readonly List<Split> splits;
    private readonly DateTime timestamp;

    public Expense(ExpenseBuilder builder)
    {
        this.id = builder.Id;
        this.description = builder.Description;
        this.amount = builder.Amount;
        this.paidBy = builder.PaidBy;
        this.timestamp = DateTime.Now;

        // Use the strategy to calculate splits
        this.splits = builder.SplitStrategy.CalculateSplits(
            builder.Amount, builder.PaidBy, builder.Participants, builder.SplitValues);
    }

    public string GetId() => id;
    public string GetDescription() => description;
    public double GetAmount() => amount;
    public User GetPaidBy() => paidBy;
    public List<Split> GetSplits() => splits;
}

class ExpenseBuilder
{
    public string Id { get; set; }
    public string Description { get; set; }
    public double Amount { get; set; }
    public User PaidBy { get; set; }
    public List<User> Participants { get; set; }
    public SplitStrategy SplitStrategy { get; set; }
    public List<double> SplitValues { get; set; }

    public ExpenseBuilder SetId(string id)
    {
        this.Id = id;
        return this;
    }

    public ExpenseBuilder SetDescription(string description)
    {
        this.Description = description;
        return this;
    }

    public ExpenseBuilder SetAmount(double amount)
    {
        this.Amount = amount;
        return this;
    }

    public ExpenseBuilder SetPaidBy(User paidBy)
    {
        this.PaidBy = paidBy;
        return this;
    }

    public ExpenseBuilder SetParticipants(List<User> participants)
    {
        this.Participants = participants;
        return this;
    }

    public ExpenseBuilder SetSplitStrategy(SplitStrategy splitStrategy)
    {
        this.SplitStrategy = splitStrategy;
        return this;
    }

    public ExpenseBuilder SetSplitValues(List<double> splitValues)
    {
        this.SplitValues = splitValues;
        return this;
    }

    public Expense Build()
    {
        if (SplitStrategy == null)
        {
            throw new InvalidOperationException("Split strategy is required.");
        }
        return new Expense(this);
    }
}