class ReadyState : IVendingMachineState
{
    public void SelectCoffee(CoffeeVendingMachine machine, Coffee coffee)
    {
        machine.SetSelectedCoffee(coffee);
        machine.SetState(new SelectingState());
        Console.WriteLine($"{coffee.GetCoffeeType()} selected. Price: {coffee.GetPrice()}");
    }

    public void InsertMoney(CoffeeVendingMachine machine, int amount)
    {
        Console.WriteLine("Please select a coffee first.");
    }

    public void DispenseCoffee(CoffeeVendingMachine machine)
    {
        Console.WriteLine("Please select and pay first.");
    }

    public void Cancel(CoffeeVendingMachine machine)
    {
        Console.WriteLine("Nothing to cancel.");
    }
}