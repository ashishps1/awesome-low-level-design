using System;

namespace Adapter
{
    public class InHousePaymentProcessor : IPaymentProcessor
    {
        private string transactionId;
        private bool isPaymentSuccessful;

        public void ProcessPayment(double amount, string currency)
        {
            try
            {
                Console.WriteLine($"InHousePaymentProcessor: Processing payment of {currency} {amount}");
                transactionId = Guid.NewGuid().ToString();
                isPaymentSuccessful = true;
                Console.WriteLine($"InHousePaymentProcessor: Payment processed successfully. Txn ID: {transactionId}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error processing payment: {ex.Message}");
                isPaymentSuccessful = false;
            }
        }

        public bool IsPaymentSuccessful()
        {
            return isPaymentSuccessful;
        }

        public string GetTransactionId()
        {
            return transactionId;
        }
    }
} 