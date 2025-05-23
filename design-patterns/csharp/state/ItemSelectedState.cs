using System;

namespace State
{
    public class ItemSelectedState : IMachineState
    {
        public void SelectItem(VendingMachine context, string itemCode)
        {
            Console.WriteLine($"Item already selected: {context.GetSelectedItem()}");
        }

        public void InsertCoin(VendingMachine context, double amount)
        {
            Console.WriteLine($"Inserted ${amount} for item: {context.GetSelectedItem()}");
            context.SetInsertedAmount(amount);
            context.SetState(new HasMoneyState());
        }

        public void DispenseItem(VendingMachine context)
        {
            Console.WriteLine("Insert coin before dispensing.");
        }
    }
} 