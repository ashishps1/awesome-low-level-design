class EqualSplitStrategy : SplitStrategy
{
    public override List<Split> CalculateSplits(double totalAmount, User paidBy, List<User> participants, List<double> splitValues)
    {
        List<Split> splits = new List<Split>();
        double amountPerPerson = totalAmount / participants.Count;
        foreach (User participant in participants)
        {
            splits.Add(new Split(participant, amountPerPerson));
        }
        return splits;
    }
}