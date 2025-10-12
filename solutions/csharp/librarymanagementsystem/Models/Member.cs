class Member
{
    private readonly string id;
    private readonly string name;
    private readonly List<Loan> loans = new List<Loan>();

    public Member(string id, string name)
    {
        this.id = id;
        this.name = name;
    }

    public void Update(LibraryItem item)
    {
        Console.WriteLine($"NOTIFICATION for {name}: The book '{item.GetTitle()}' you placed a hold on is now available!");
    }

    public void AddLoan(Loan loan) { loans.Add(loan); }
    public void RemoveLoan(Loan loan) { loans.Remove(loan); }
    public string GetId() { return id; }
    public string GetName() { return name; }
    public List<Loan> GetLoans() { return loans; }
}