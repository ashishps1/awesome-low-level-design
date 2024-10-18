using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Numerics;

namespace DigitalWallet
{
    public class DigitalWallet
    {
        private static DigitalWallet instance;
        private readonly ConcurrentDictionary<string, User> users;
        private readonly ConcurrentDictionary<string, Account> accounts;
        private readonly ConcurrentDictionary<string, PaymentMethod> paymentMethods;

        private DigitalWallet()
        {
            users = new ConcurrentDictionary<string, User>();
            accounts = new ConcurrentDictionary<string, Account>();
            paymentMethods = new ConcurrentDictionary<string, PaymentMethod>();
        }

        public static DigitalWallet GetInstance()
        {
            if (instance == null)
            {
                instance = new DigitalWallet();
            }
            return instance;
        }

        public void CreateUser(User user)
        {
            users[user.GetId()] = user;
        }

        public User GetUser(string userId)
        {
            return users.ContainsKey(userId) ? users[userId] : null;
        }

        public void CreateAccount(Account account)
        {
            accounts[account.GetId()] = account;
            account.GetUser().AddAccount(account);
        }

        public Account GetAccount(string accountId)
        {
            return accounts.ContainsKey(accountId) ? accounts[accountId] : null;
        }

        public void AddPaymentMethod(PaymentMethod paymentMethod)
        {
            paymentMethods[paymentMethod.GetId()] = paymentMethod;
        }

        public PaymentMethod GetPaymentMethod(string paymentMethodId)
        {
            return paymentMethods.ContainsKey(paymentMethodId) ? paymentMethods[paymentMethodId] : null;
        }

        public void TransferFunds(Account sourceAccount, Account destinationAccount, decimal amount, Currency currency)
        {
            if (sourceAccount.GetCurrency() != currency)
            {
                amount = CurrencyConverter.Convert(amount, currency, sourceAccount.GetCurrency());
            }
            sourceAccount.Withdraw(amount);

            if (destinationAccount.GetCurrency() != currency)
            {
                amount = CurrencyConverter.Convert(amount, currency, destinationAccount.GetCurrency());
            }
            destinationAccount.Deposit(amount);

            string transactionId = GenerateTransactionId();
            Transaction transaction = new Transaction(transactionId, sourceAccount, destinationAccount, amount, currency);
            sourceAccount.AddTransaction(transaction);
            destinationAccount.AddTransaction(transaction);
        }

        public List<Transaction> GetTransactionHistory(Account account)
        {
            return account.GetTransactions();
        }

        private string GenerateTransactionId()
        {
            return "TXN" + Guid.NewGuid().ToString().Substring(0, 8).ToUpper();
        }
    }
}