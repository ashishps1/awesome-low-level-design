using System;
using System.Collections.Concurrent;

namespace ATM
{
    public class BankingService
    {
        private readonly ConcurrentDictionary<string, Account> accounts = new ConcurrentDictionary<string, Account>();

        public void CreateAccount(string accountNumber, double initialBalance)
        {
            accounts[accountNumber] = new Account(accountNumber, initialBalance);
        }

        public Account GetAccount(string accountNumber)
        {
            accounts.TryGetValue(accountNumber, out var account);
            return account;
        }

        public void ProcessTransaction(Transaction transaction)
        {
            transaction.Execute();
        }
    }
}