abstract class VendingMachineState
{
    protected VendingMachine machine;

    public VendingMachineState(VendingMachine machine)
    {
        this.machine = machine;
    }

    public abstract void InsertCoin(Coin coin);
    public abstract void SelectItem(string code);
    public abstract void Dispense();
    public abstract void Refund();
}