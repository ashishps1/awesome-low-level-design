using System;

namespace DigitalWallet
{
    public class InsufficientFundsException : Exception
    {
        public InsufficientFundsException(string message) : base(message) { }
    }
}