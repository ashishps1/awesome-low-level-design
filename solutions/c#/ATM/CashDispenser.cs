using System;

namespace ATM
{
    public class CashDispenser
    {
        private int cashAvailable;

        public CashDispenser(int initialCash)
        {
            cashAvailable = initialCash;
        }

        public void DispenseCash(int amount)
        {
            lock (this)
            {
                if (amount > cashAvailable)
                {
                    throw new ArgumentException("Insufficient cash available in the ATM.");
                }
                cashAvailable -= amount;
                Console.WriteLine("Cash dispensed: " + amount);
            }
        }
    }
}