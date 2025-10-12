class SplitwiseService
{
    private static SplitwiseService instance;
    private static readonly object lockObject = new object();
    private readonly Dictionary<string, User> users = new Dictionary<string, User>();
    private readonly Dictionary<string, Group> groups = new Dictionary<string, Group>();

    private SplitwiseService() { }

    public static SplitwiseService GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new SplitwiseService();
                }
            }
        }
        return instance;
    }

    public User AddUser(string name, string email)
    {
        User user = new User(name, email);
        users[user.GetId()] = user;
        return user;
    }

    public Group AddGroup(string name, List<User> members)
    {
        Group group = new Group(name, members);
        groups[group.GetId()] = group;
        return group;
    }

    public User GetUser(string id)
    {
        return users.TryGetValue(id, out User user) ? user : null;
    }

    public Group GetGroup(string id)
    {
        return groups.TryGetValue(id, out Group group) ? group : null;
    }

    public void CreateExpense(ExpenseBuilder builder)
    {
        lock (lockObject)
        {
            Expense expense = builder.Build();
            User paidBy = expense.GetPaidBy();

            foreach (Split split in expense.GetSplits())
            {
                User participant = split.GetUser();
                double amount = split.GetAmount();

                if (!paidBy.Equals(participant))
                {
                    paidBy.GetBalanceSheet().AdjustBalance(participant, amount);
                    participant.GetBalanceSheet().AdjustBalance(paidBy, -amount);
                }
            }

            Console.WriteLine($"Expense '{expense.GetDescription()}' of amount {expense.GetAmount()} created.");
        }
    }

    public void SettleUp(string payerId, string payeeId, double amount)
    {
        lock (lockObject)
        {
            User payer = users[payerId];
            User payee = users[payeeId];
            Console.WriteLine($"{payer.GetName()} is settling up {amount} with {payee.GetName()}");

            // Settlement is like a reverse expense. payer owes less to payee.
            payee.GetBalanceSheet().AdjustBalance(payer, -amount);
            payer.GetBalanceSheet().AdjustBalance(payee, amount);
        }
    }

    public void ShowBalanceSheet(string userId)
    {
        User user = users[userId];
        user.GetBalanceSheet().ShowBalances();
    }

    public List<Transaction> SimplifyGroupDebts(string groupId)
    {
        Group group = groups[groupId];
        if (group == null)
        {
            throw new ArgumentException("Group not found");
        }

        // Calculate net balance for each member within the group context
        Dictionary<User, double> netBalances = new Dictionary<User, double>();
        foreach (User member in group.GetMembers())
        {
            double balance = 0;
            foreach (var entry in member.GetBalanceSheet().GetBalances())
            {
                // Consider only balances with other group members
                if (group.GetMembers().Contains(entry.Key))
                {
                    balance += entry.Value;
                }
            }
            netBalances[member] = balance;
        }

        // Separate into creditors and debtors
        var creditors = netBalances.Where(e => e.Value > 0).OrderByDescending(e => e.Value).ToList();
        var debtors = netBalances.Where(e => e.Value < 0).OrderBy(e => e.Value).ToList();

        List<Transaction> transactions = new List<Transaction>();
        int i = 0, j = 0;

        while (i < creditors.Count && j < debtors.Count)
        {
            var creditor = creditors[i];
            var debtor = debtors[j];

            double amountToSettle = Math.Min(creditor.Value, -debtor.Value);
            transactions.Add(new Transaction(debtor.Key, creditor.Key, amountToSettle));

            // Update the values
            creditors[i] = new KeyValuePair<User, double>(creditor.Key, creditor.Value - amountToSettle);
            debtors[j] = new KeyValuePair<User, double>(debtor.Key, debtor.Value + amountToSettle);

            if (Math.Abs(creditors[i].Value) < 0.01) i++;
            if (Math.Abs(debtors[j].Value) < 0.01) j++;
        }

        return transactions;
    }
}