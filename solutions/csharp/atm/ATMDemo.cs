using System;

namespace ATM
{
    public class ATMDemo
    {
        public static void Run()
        {
            var bankingService = new BankingService();
            var cashDispenser = new CashDispenser(10000);
            var atm = new ATM(bankingService, cashDispenser);

            // Create sample accounts
            bankingService.CreateAccount("1234567890", 1000.0);
            bankingService.CreateAccount("9876543210", 500.0);

            // Perform ATM operations
            var card = new Card("1234567890", "1234");
            atm.AuthenticateUser(card);

            double balance = atm.CheckBalance("1234567890");
            Console.WriteLine("Account balance: " + balance);

            atm.WithdrawCash("1234567890", 500.0);
            atm.DepositCash("9876543210", 200.0);

            balance = atm.CheckBalance("1234567890");
            Console.WriteLine("Updated account balance: " + balance);
        }
    }
}