class IdleState : VendingMachineState
{
    public IdleState(VendingMachine machine) : base(machine)
    {
    }

    public override void InsertCoin(Coin coin)
    {
        Console.WriteLine("Please select an item before inserting money.");
    }

    public override void SelectItem(string code)
    {
        if (!machine.GetInventory().IsAvailable(code))
        {
            Console.WriteLine("Item not available.");
            return;
        }
        machine.SetSelectedItemCode(code);
        machine.SetState(new ItemSelectedState(machine));
        Console.WriteLine("Item selected: " + code);
    }

    public override void Dispense()
    {
        Console.WriteLine("No item selected.");
    }

    public override void Refund()
    {
        Console.WriteLine("No money to refund.");
    }
}