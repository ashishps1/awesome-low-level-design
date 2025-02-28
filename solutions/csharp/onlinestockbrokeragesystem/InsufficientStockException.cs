using System;

namespace OnlineStockBrokerageSystem
{
    public class InsufficientStockException : Exception
    {
        public InsufficientStockException(string message) : base(message)
        {
        }
    }
}