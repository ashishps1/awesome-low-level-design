class Split
{
    private readonly User user;
    private readonly double amount;

    public Split(User user, double amount)
    {
        this.user = user;
        this.amount = amount;
    }

    public User GetUser() => user;
    public double GetAmount() => amount;
}