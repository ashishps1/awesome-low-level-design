using System;
using System.Numerics;

namespace DigitalWallet
{
    public abstract class PaymentMethod
    {
        protected readonly string id;
        protected readonly User user;

        protected PaymentMethod(string id, User user)
        {
            this.id = id;
            this.user = user;
        }

        public abstract bool ProcessPayment(decimal amount, Currency currency);

        public string GetId()
        {
            return id;
        }

        public User GetUser()
        {
            return user;
        }
    }
}