class ExactSplitStrategy : SplitStrategy
{
    public override List<Split> CalculateSplits(double totalAmount, User paidBy, List<User> participants, List<double> splitValues)
    {
        if (participants.Count != splitValues.Count)
        {
            throw new ArgumentException("Number of participants and split values must match.");
        }

        if (Math.Abs(splitValues.Sum() - totalAmount) > 0.01)
        {
            throw new ArgumentException("Sum of exact amounts must equal the total expense amount.");
        }

        List<Split> splits = new List<Split>();
        for (int i = 0; i < participants.Count; i++)
        {
            splits.Add(new Split(participants[i], splitValues[i]));
        }
        return splits;
    }
}