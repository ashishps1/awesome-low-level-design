class BalanceSheet
{
    private readonly User owner;
    private readonly Dictionary<User, double> balances = new Dictionary<User, double>();
    private readonly object balanceLock = new object();

    public BalanceSheet(User owner)
    {
        this.owner = owner;
    }

    public Dictionary<User, double> GetBalances() => balances;

    public void AdjustBalance(User otherUser, double amount)
    {
        lock (balanceLock)
        {
            if (owner.Equals(otherUser))
            {
                return; // Cannot owe yourself
            }

            if (balances.ContainsKey(otherUser))
            {
                balances[otherUser] += amount;
            }
            else
            {
                balances[otherUser] = amount;
            }
        }
    }

    public void ShowBalances()
    {
        Console.WriteLine($"--- Balance Sheet for {owner.GetName()} ---");
        if (balances.Count == 0)
        {
            Console.WriteLine("All settled up!");
            return;
        }

        double totalOwedToMe = 0;
        double totalIOwe = 0;

        foreach (var entry in balances)
        {
            User otherUser = entry.Key;
            double amount = entry.Value;

            if (amount > 0.01)
            {
                Console.WriteLine($"{otherUser.GetName()} owes {owner.GetName()} ${amount:F2}");
                totalOwedToMe += amount;
            }
            else if (amount < -0.01)
            {
                Console.WriteLine($"{owner.GetName()} owes {otherUser.GetName()} ${-amount:F2}");
                totalIOwe += (-amount);
            }
        }

        Console.WriteLine($"Total Owed to {owner.GetName()}: ${totalOwedToMe:F2}");
        Console.WriteLine($"Total {owner.GetName()} Owes: ${totalIOwe:F2}");
        Console.WriteLine("---------------------------------");
    }
}