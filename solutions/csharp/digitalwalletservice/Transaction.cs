using System;
using System.Numerics;

namespace DigitalWallet
{
    public class Transaction
    {
        private readonly string id;
        private readonly Account sourceAccount;
        private readonly Account destinationAccount;
        private readonly decimal amount;
        private readonly Currency currency;
        private readonly DateTime timestamp;

        public Transaction(string id, Account sourceAccount, Account destinationAccount, decimal amount, Currency currency)
        {
            this.id = id;
            this.sourceAccount = sourceAccount;
            this.destinationAccount = destinationAccount;
            this.amount = amount;
            this.currency = currency;
            this.timestamp = DateTime.Now;
        }

        public string GetId()
        {
            return id;
        }

        public Account GetSourceAccount()
        {
            return sourceAccount;
        }

        public Account GetDestinationAccount()
        {
            return destinationAccount;
        }

        public decimal GetAmount()
        {
            return amount;
        }

        public Currency GetCurrency()
        {
            return currency;
        }

        public DateTime GetTimestamp()
        {
            return timestamp;
        }
    }
}