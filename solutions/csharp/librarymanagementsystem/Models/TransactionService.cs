class TransactionService
{
    private static readonly TransactionService instance = new TransactionService();
    private readonly Dictionary<string, Loan> activeLoans = new Dictionary<string, Loan>();

    private TransactionService() { }
    public static TransactionService GetInstance() { return instance; }

    public void CreateLoan(BookCopy copy, Member member)
    {
        if (activeLoans.ContainsKey(copy.GetId()))
        {
            throw new InvalidOperationException("This copy is already on loan.");
        }
        
        var loan = new Loan(copy, member);
        activeLoans[copy.GetId()] = loan;
        member.AddLoan(loan);
    }

    public void EndLoan(BookCopy copy)
    {
        if (activeLoans.TryGetValue(copy.GetId(), out var loan))
        {
            activeLoans.Remove(copy.GetId());
            loan.GetMember().RemoveLoan(loan);
        }
    }
}