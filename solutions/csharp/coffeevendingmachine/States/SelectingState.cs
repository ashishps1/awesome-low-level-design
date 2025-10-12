class SelectingState : IVendingMachineState
{
    public void SelectCoffee(CoffeeVendingMachine machine, Coffee coffee)
    {
        Console.WriteLine("Already selected. Please pay or cancel.");
    }

    public void InsertMoney(CoffeeVendingMachine machine, int amount)
    {
        machine.SetMoneyInserted(machine.GetMoneyInserted() + amount);
        Console.WriteLine($"Inserted {amount}. Total: {machine.GetMoneyInserted()}");
        if (machine.GetMoneyInserted() >= machine.GetSelectedCoffee().GetPrice())
        {
            machine.SetState(new PaidState());
        }
    }

    public void DispenseCoffee(CoffeeVendingMachine machine)
    {
        Console.WriteLine("Please insert enough money first.");
    }

    public void Cancel(CoffeeVendingMachine machine)
    {
        Console.WriteLine($"Transaction cancelled. Refunding {machine.GetMoneyInserted()}");
        machine.Reset();
        machine.SetState(new ReadyState());
    }
}