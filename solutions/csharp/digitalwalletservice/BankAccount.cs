using System;
using System.Numerics;

namespace DigitalWallet
{
    public class BankAccount : PaymentMethod
    {
        private readonly string accountNumber;
        private readonly string routingNumber;

        public BankAccount(string id, User user, string accountNumber, string routingNumber)
            : base(id, user)
        {
            this.accountNumber = accountNumber;
            this.routingNumber = routingNumber;
        }

        public override bool ProcessPayment(decimal amount, Currency currency)
        {
            // Process bank account payment logic
            return true;
        }
    }
}