class OutOfIngredientState : IVendingMachineState
{
    public void SelectCoffee(CoffeeVendingMachine machine, Coffee coffee)
    {
        Console.WriteLine("Sorry, we are sold out.");
    }

    public void InsertMoney(CoffeeVendingMachine machine, int amount)
    {
        Console.WriteLine("Sorry, we are sold out. Money refunded.");
    }

    public void DispenseCoffee(CoffeeVendingMachine machine)
    {
        Console.WriteLine("Sorry, we are sold out.");
    }

    public void Cancel(CoffeeVendingMachine machine)
    {
        Console.WriteLine($"Refunding {machine.GetMoneyInserted()}");
        machine.Reset();
        machine.SetState(new ReadyState());
    }
}