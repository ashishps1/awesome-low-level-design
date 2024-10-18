using System;
using System.Collections.Generic;
using System.Numerics;

namespace DigitalWallet
{
    public class DigitalWalletDemo
    {
        public static void Run()
        {
            DigitalWallet digitalWallet = DigitalWallet.GetInstance();

            // Create users
            User user1 = new User("U001", "John Doe", "john@example.com", "password123");
            User user2 = new User("U002", "Jane Smith", "jane@example.com", "password456");
            digitalWallet.CreateUser(user1);
            digitalWallet.CreateUser(user2);

            // Create accounts
            Account account1 = new Account("A001", user1, "1234567890", Currency.USD);
            Account account2 = new Account("A002", user2, "9876543210", Currency.EUR);
            digitalWallet.CreateAccount(account1);
            digitalWallet.CreateAccount(account2);

            // Add payment methods
            PaymentMethod creditCard = new CreditCard("PM001", user1, "1234567890123456", "12/25", "123");
            PaymentMethod bankAccount = new BankAccount("PM002", user2, "9876543210", "987654321");
            digitalWallet.AddPaymentMethod(creditCard);
            digitalWallet.AddPaymentMethod(bankAccount);

            // Deposit funds
            account1.Deposit(1000.00M);
            account2.Deposit(500.00M);

            // Transfer funds
            digitalWallet.TransferFunds(account1, account2, 100.00M, Currency.USD);

            // Get transaction history
            List<Transaction> transactionHistory1 = digitalWallet.GetTransactionHistory(account1);
            List<Transaction> transactionHistory2 = digitalWallet.GetTransactionHistory(account2);

            // Print transaction history
            Console.WriteLine("Transaction History for Account 1:");
            foreach (Transaction transaction in transactionHistory1)
            {
                Console.WriteLine("Transaction ID: " + transaction.GetId());
                Console.WriteLine("Amount: " + transaction.GetAmount() + " " + transaction.GetCurrency());
                Console.WriteLine("Timestamp: " + transaction.GetTimestamp());
                Console.WriteLine();
            }

            Console.WriteLine("Transaction History for Account 2:");
            foreach (Transaction transaction in transactionHistory2)
            {
                Console.WriteLine("Transaction ID: " + transaction.GetId());
                Console.WriteLine("Amount: " + transaction.GetAmount() + " " + transaction.GetCurrency());
                Console.WriteLine("Timestamp: " + transaction.GetTimestamp());
                Console.WriteLine();
            }
        }
    }
}