namespace Splitwise
{
    public class PercentSplit : Split
    {
        public double Percent { get; }

        public PercentSplit(User user, double percent) : base(user)
        {
            Percent = percent;
        }

        public override double Amount { get; set; }
    }
}