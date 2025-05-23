using System;

namespace Adapter
{
    public class LegacyGatewayAdapter : IPaymentProcessor
    {
        private readonly LegacyGateway legacyGateway;
        private bool isPaymentSuccessful;

        public LegacyGatewayAdapter()
        {
            legacyGateway = new LegacyGateway();
        }

        public void ProcessPayment(double amount, string currency)
        {
            try
            {
                legacyGateway.ExecuteTransaction(amount, currency);
                isPaymentSuccessful = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error processing payment: {ex.Message}");
                isPaymentSuccessful = false;
            }
        }

        public bool IsPaymentSuccessful()
        {
            return isPaymentSuccessful && 
                   legacyGateway.CheckStatus(legacyGateway.GetReferenceNumber());
        }

        public string GetTransactionId()
        {
            return legacyGateway.GetReferenceNumber().ToString();
        }
    }
} 