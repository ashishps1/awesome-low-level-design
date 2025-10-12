class PercentageSplitStrategy : SplitStrategy
{
    public override List<Split> CalculateSplits(double totalAmount, User paidBy, List<User> participants, List<double> splitValues)
    {
        if (participants.Count != splitValues.Count)
        {
            throw new ArgumentException("Number of participants and split values must match.");
        }

        if (Math.Abs(splitValues.Sum() - 100.0) > 0.01)
        {
            throw new ArgumentException("Sum of percentages must be 100.");
        }

        List<Split> splits = new List<Split>();
        for (int i = 0; i < participants.Count; i++)
        {
            double amount = (totalAmount * splitValues[i]) / 100.0;
            splits.Add(new Split(participants[i], amount));
        }
        return splits;
    }
}