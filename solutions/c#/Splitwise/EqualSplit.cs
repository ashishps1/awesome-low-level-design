namespace Splitwise
{
    public class EqualSplit : Split
    {
        public EqualSplit(User user) : base(user) { }

        public override double Amount { get; set; }
    }
}