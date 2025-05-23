using System;

namespace State
{
    class Program
    {
        static void Main(string[] args)
        {
            var vm = new VendingMachine();

            vm.InsertCoin(1.0); // Invalid in IdleState
            vm.SelectItem("A1");
            vm.InsertCoin(1.5);
            vm.DispenseItem();

            Console.WriteLine("\n--- Second Transaction ---");
            vm.SelectItem("B2");
            vm.InsertCoin(2.0);
            vm.DispenseItem();
        }
    }
} 