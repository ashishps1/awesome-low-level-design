using System;
using System.Threading;

namespace State
{
    public class HasMoneyState : IMachineState
    {
        public void SelectItem(VendingMachine context, string itemCode)
        {
            Console.WriteLine("Cannot change item after inserting money.");
        }

        public void InsertCoin(VendingMachine context, double amount)
        {
            Console.WriteLine("Money already inserted.");
        }

        public void DispenseItem(VendingMachine context)
        {
            Console.WriteLine($"Dispensing item: {context.GetSelectedItem()}");
            context.SetState(new DispensingState());

            // Simulate dispensing
            Thread.Sleep(1000);

            Console.WriteLine("Item dispensed successfully.");
            context.Reset();
        }
    }
} 