class IdleState : IATMState
{
    public void InsertCard(ATM atm, string cardNumber)
    {
        Console.WriteLine("\nCard has been inserted.");
        Card card = atm.GetBankService().AuthenticateCard(cardNumber);

        if (card == null)
        {
            EjectCard(atm);
        }
        else
        {
            atm.SetCurrentCard(card);
            atm.ChangeState(new HasCardState());
        }
    }

    public void EnterPin(ATM atm, string pin)
    {
        Console.WriteLine("Error: Please insert a card first.");
    }

    public void SelectOperation(ATM atm, OperationType op, int amount = 0)
    {
        Console.WriteLine("Error: Please insert a card first.");
    }

    public void EjectCard(ATM atm)
    {
        Console.WriteLine("Error: Card not found.");
        atm.SetCurrentCard(null);
    }
}