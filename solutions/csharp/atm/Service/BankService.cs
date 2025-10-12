class BankService
{
    private readonly Dictionary<string, Account> accounts = new Dictionary<string, Account>();
    private readonly Dictionary<string, Card> cards = new Dictionary<string, Card>();
    private readonly Dictionary<Card, Account> cardAccountMap = new Dictionary<Card, Account>();

    public BankService()
    {
        // Create sample accounts and cards
        Account account1 = CreateAccount("1234567890", 1000.0);
        Card card1 = CreateCard("1234-5678-9012-3456", "1234");
        LinkCardToAccount(card1, account1);

        Account account2 = CreateAccount("9876543210", 500.0);
        Card card2 = CreateCard("9876-5432-1098-7654", "4321");
        LinkCardToAccount(card2, account2);
    }

    public Account CreateAccount(string accountNumber, double initialBalance)
    {
        Account account = new Account(accountNumber, initialBalance);
        accounts[accountNumber] = account;
        return account;
    }

    public Card CreateCard(string cardNumber, string pin)
    {
        Card card = new Card(cardNumber, pin);
        cards[cardNumber] = card;
        return card;
    }

    public bool Authenticate(Card card, string pin)
    {
        return card.GetPin() == pin;
    }

    public Card AuthenticateCard(string cardNumber)
    {
        return cards.TryGetValue(cardNumber, out Card card) ? card : null;
    }

    public double GetBalance(Card card)
    {
        return cardAccountMap[card].GetBalance();
    }

    public void WithdrawMoney(Card card, double amount)
    {
        cardAccountMap[card].Withdraw(amount);
    }

    public void DepositMoney(Card card, double amount)
    {
        cardAccountMap[card].Deposit(amount);
    }

    public void LinkCardToAccount(Card card, Account account)
    {
        account.GetCards()[card.GetCardNumber()] = card;
        cardAccountMap[card] = account;
    }
}