namespace Splitwise
{
    public abstract class Split
    {
        public User User { get; }
        public abstract double Amount { get; set; }

        protected Split(User user)
        {
            User = user;
        }
    }
}