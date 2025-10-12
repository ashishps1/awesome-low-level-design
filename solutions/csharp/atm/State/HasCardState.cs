class HasCardState : IATMState
{
    public void InsertCard(ATM atm, string cardNumber)
    {
        Console.WriteLine("Error: A card is already inserted. Cannot insert another card.");
    }

    public void EnterPin(ATM atm, string pin)
    {
        Console.WriteLine("Authenticating PIN...");
        Card card = atm.GetCurrentCard();
        bool isAuthenticated = atm.GetBankService().Authenticate(card, pin);

        if (isAuthenticated)
        {
            Console.WriteLine("Authentication successful.");
            atm.ChangeState(new AuthenticatedState());
        }
        else
        {
            Console.WriteLine("Authentication failed: Incorrect PIN.");
            EjectCard(atm);
        }
    }

    public void SelectOperation(ATM atm, OperationType op, int amount = 0)
    {
        Console.WriteLine("Error: Please enter your PIN first to select an operation.");
    }

    public void EjectCard(ATM atm)
    {
        Console.WriteLine("Card has been ejected. Thank you for using our ATM.");
        atm.SetCurrentCard(null);
        atm.ChangeState(new IdleState());
    }
}