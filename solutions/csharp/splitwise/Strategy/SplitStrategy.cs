abstract class SplitStrategy
{
    public abstract List<Split> CalculateSplits(double totalAmount, User paidBy, List<User> participants, List<double> splitValues);
}