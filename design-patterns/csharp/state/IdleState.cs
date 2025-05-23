using System;

namespace State
{
    public class IdleState : IMachineState
    {
        public void SelectItem(VendingMachine context, string itemCode)
        {
            Console.WriteLine($"Item selected: {itemCode}");
            context.SetSelectedItem(itemCode);
            context.SetState(new ItemSelectedState());
        }

        public void InsertCoin(VendingMachine context, double amount)
        {
            Console.WriteLine("Please select an item before inserting coins.");
        }

        public void DispenseItem(VendingMachine context)
        {
            Console.WriteLine("No item selected. Nothing to dispense.");
        }
    }
} 