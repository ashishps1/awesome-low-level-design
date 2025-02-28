using System;
using System.Numerics;

namespace DigitalWallet
{
    public class CreditCard : PaymentMethod
    {
        private readonly string cardNumber;
        private readonly string expirationDate;
        private readonly string cvv;

        public CreditCard(string id, User user, string cardNumber, string expirationDate, string cvv)
            : base(id, user)
        {
            this.cardNumber = cardNumber;
            this.expirationDate = expirationDate;
            this.cvv = cvv;
        }

        public override bool ProcessPayment(decimal amount, Currency currency)
        {
            // Process credit card payment logic
            return true;
        }
    }
}