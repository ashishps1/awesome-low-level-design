class ATM
{
    private static ATM instance;
    private static readonly object lockObject = new object();
    private readonly BankService bankService;
    private readonly CashDispenser cashDispenser;
    private static long transactionCounter = 0;
    private IATMState currentState;
    private Card currentCard;

    private ATM()
    {
        currentState = new IdleState();
        bankService = new BankService();

        // Setup the dispenser chain
        IDispenseChain c1 = new NoteDispenser100(10); // 10 x $100 notes
        IDispenseChain c2 = new NoteDispenser50(20);  // 20 x $50 notes
        IDispenseChain c3 = new NoteDispenser20(30);  // 30 x $20 notes
        c1.SetNextChain(c2);
        c2.SetNextChain(c3);
        cashDispenser = new CashDispenser(c1);
    }

    public static ATM GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new ATM();
                }
            }
        }
        return instance;
    }

    public void ChangeState(IATMState newState)
    {
        currentState = newState;
    }

    public void SetCurrentCard(Card card)
    {
        currentCard = card;
    }

    public void InsertCard(string cardNumber)
    {
        currentState.InsertCard(this, cardNumber);
    }

    public void EnterPin(string pin)
    {
        currentState.EnterPin(this, pin);
    }

    public void SelectOperation(OperationType op, int amount = 0)
    {
        currentState.SelectOperation(this, op, amount);
    }

    public void CheckBalance()
    {
        double balance = bankService.GetBalance(currentCard);
        Console.WriteLine($"Your current account balance is: ${balance:F2}");
    }

    public void WithdrawCash(int amount)
    {
        if (!cashDispenser.CanDispenseCash(amount))
        {
            throw new InvalidOperationException("Insufficient cash available in the ATM.");
        }

        bankService.WithdrawMoney(currentCard, amount);

        try
        {
            cashDispenser.DispenseCash(amount);
        }
        catch (Exception)
        {
            bankService.DepositMoney(currentCard, amount); // Deposit back if dispensing fails
            throw;
        }
    }

    public void DepositCash(int amount)
    {
        bankService.DepositMoney(currentCard, amount);
    }

    public Card GetCurrentCard() => currentCard;
    public BankService GetBankService() => bankService;
}