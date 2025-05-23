namespace State
{
    public interface IMachineState
    {
        void SelectItem(VendingMachine context, string itemCode);
        void InsertCoin(VendingMachine context, double amount);
        void DispenseItem(VendingMachine context);
    }
} 