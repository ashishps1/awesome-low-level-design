using System;

namespace State
{
    public class DispensingState : IMachineState
    {
        public void SelectItem(VendingMachine context, string itemCode)
        {
            Console.WriteLine("Please wait, dispensing in progress.");
        }

        public void InsertCoin(VendingMachine context, double amount)
        {
            Console.WriteLine("Please wait, dispensing in progress.");
        }

        public void DispenseItem(VendingMachine context)
        {
            Console.WriteLine("Already dispensing. Please wait.");
        }
    }
} 