class User
{
    private readonly string id;
    private readonly string name;
    private readonly string email;
    private readonly BalanceSheet balanceSheet;

    public User(string name, string email)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.email = email;
        this.balanceSheet = new BalanceSheet(this);
    }

    public string GetId() => id;
    public string GetName() => name;
    public BalanceSheet GetBalanceSheet() => balanceSheet;
}