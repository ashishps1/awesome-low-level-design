class AuthenticatedState : IATMState
{
    public void InsertCard(ATM atm, string cardNumber)
    {
        Console.WriteLine("Error: A card is already inserted and a session is active.");
    }

    public void EnterPin(ATM atm, string pin)
    {
        Console.WriteLine("Error: PIN has already been entered and authenticated.");
    }

    public void SelectOperation(ATM atm, OperationType op, int amount = 0)
    {
        switch (op)
        {
            case OperationType.CHECK_BALANCE:
                atm.CheckBalance();
                break;

            case OperationType.WITHDRAW_CASH:
                if (amount <= 0)
                {
                    Console.WriteLine("Error: Invalid withdrawal amount specified.");
                    break;
                }

                double accountBalance = atm.GetBankService().GetBalance(atm.GetCurrentCard());
                if (amount > accountBalance)
                {
                    Console.WriteLine("Error: Insufficient balance.");
                    break;
                }

                Console.WriteLine($"Processing withdrawal for ${amount}");
                atm.WithdrawCash(amount);
                break;

            case OperationType.DEPOSIT_CASH:
                if (amount <= 0)
                {
                    Console.WriteLine("Error: Invalid deposit amount specified.");
                    break;
                }
                Console.WriteLine($"Processing deposit for ${amount}");
                atm.DepositCash(amount);
                break;

            default:
                Console.WriteLine("Error: Invalid operation selected.");
                break;
        }

        // End the session after one transaction
        Console.WriteLine("Transaction complete.");
        EjectCard(atm);
    }

    public void EjectCard(ATM atm)
    {
        Console.WriteLine("Ending session. Card has been ejected. Thank you for using our ATM.");
        atm.SetCurrentCard(null);
        atm.ChangeState(new IdleState());
    }
}