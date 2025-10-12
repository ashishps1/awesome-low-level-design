class DispensingState : VendingMachineState
{
    public DispensingState(VendingMachine machine) : base(machine)
    {
    }

    public override void InsertCoin(Coin coin)
    {
        Console.WriteLine("Currently dispensing. Please wait.");
    }

    public override void SelectItem(string code)
    {
        Console.WriteLine("Currently dispensing. Please wait.");
    }

    public override void Dispense()
    {
        // already triggered by HasMoneyState
    }

    public override void Refund()
    {
        Console.WriteLine("Dispensing in progress. Refund not allowed.");
    }
}