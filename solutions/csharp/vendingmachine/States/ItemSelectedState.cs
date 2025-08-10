class ItemSelectedState : VendingMachineState
{
    public ItemSelectedState(VendingMachine machine) : base(machine)
    {
    }

    public override void InsertCoin(Coin coin)
    {
        machine.AddBalance((int)coin);
        Console.WriteLine("Coin Inserted: " + (int)coin);
        int price = machine.GetSelectedItem().GetPrice();
        if (machine.GetBalance() >= price)
        {
            Console.WriteLine("Sufficient money received.");
            machine.SetState(new HasMoneyState(machine));
        }
    }

    public override void SelectItem(string code)
    {
        Console.WriteLine("Item already selected.");
    }

    public override void Dispense()
    {
        Console.WriteLine("Please insert sufficient money.");
    }

    public override void Refund()
    {
        machine.Reset();
        machine.SetState(new IdleState(machine));
    }
}